#include <thread>

#include "TMinesweeperGameRunner.h"
#include "TMinesweeperGame.h"
#include "TFieldDrawer.h"

using namespace std;

TMinesweeperGameRunner::TMinesweeperGameRunner( TRenderer& rendererRef )
    : renderer( rendererRef )
{
}

void TMinesweeperGameRunner::init()
{
    cellsFieldParams.xCellsCount = 20;
    cellsFieldParams.yCellsCount = 15;
    cellsFieldParams.cellHeight = 32;
    cellsFieldParams.cellWidth = 32;
}

void TMinesweeperGameRunner::run()
{
    TCellRectangles mainFieldCellsGrid;
    mainFieldCellsGrid.setCellsFieldParams( activeGameField, cellsFieldParams );
    mainFieldCellsGrid.calcGrid();

    TMinesweeperGame game( { cellsFieldParams.yCellsCount, cellsFieldParams.xCellsCount  } );

    game.minesweeper.initializeField( cellsFieldParams.yCellsCount, cellsFieldParams.xCellsCount, 40 );

    vector<TSurface> surfaces;
    vector<TTexture> textures;

    for ( size_t i = 0; i < 16; ++i )
    {
        surfaces.emplace_back( "minesweeper_sprites.bmp" );
        textures.emplace_back( renderer );
    }

    for ( size_t i = 0; i < 16; ++i )
    {
        textures[i].updateSurface( surfaces[i] );
        textures[i].setTexturePart( { i * 32, 0 }, { 32, 32 } );
        textures[i].setStartPoint( { i * 20 + 60, 500 } );
    }

    TTexturesFieldDrawer fieldDrawer( game.gameField, renderer, mainFieldCellsGrid );
    fieldDrawer.textures = &textures;
    fieldDrawer.textureSliceSize = { 32, 32 };
    fieldDrawer.cellsMapper = []( const TCell& cell )
    {
        constexpr int biasIndex = 7;

        if ( cell.currentState == "h" )
           return 0;

        if ( cell.currentState == "f" )
           return 3;

        if ( cell.currentState == "b" )
           return 2;

        if ( cell.currentState == "0" )
           return 1;

        if ( cell.currentState == "1" )
           return 1 + biasIndex;

        if ( cell.currentState == "2" )
           return 2 + biasIndex;

        if ( cell.currentState == "3" )
           return 3 + biasIndex;

        if ( cell.currentState == "4" )
           return 4 + biasIndex;

        if ( cell.currentState == "5" )
           return 5 + biasIndex;

        if ( cell.currentState == "6" )
           return 6 + biasIndex;

        if ( cell.currentState == "7" )
           return 7 + biasIndex;

        if ( cell.currentState == "8" )
           return 8 + biasIndex;

        return 0;
    };

    TFontDrawer statusTextDrawer( renderer, fontFile, fontSize + 6 );
    statusTextDrawer.getFontDrawerRef().setPoint( { 600, 10 }, TTextAlignment::centerAlignment );
    statusTextDrawer.setText( "Uninitialized" );
    statusTextDrawer.isVisible = false;

    TFontDrawer titleTextDrawer( renderer, fontFile, fontSize + 10 );
    titleTextDrawer.setText( "Minesweeper" );
    titleTextDrawer.getFontDrawerRef().setPoint( { 400, 10 }, TTextAlignment::centerAlignment );
    titleTextDrawer.isVisible = true;

    TFontDrawer flagsCountTextDrawer( renderer, fontFile, fontSize + 6 );
    flagsCountTextDrawer.setText( "Flags: " );
    flagsCountTextDrawer.getFontDrawerRef().setPoint( { 75, 550 }, TTextAlignment::leftAlignment );
    flagsCountTextDrawer.isVisible = true;

    TFontDrawer currentTimeTextDrawer( renderer, fontFile, fontSize + 6 );
    currentTimeTextDrawer.setText( "Time: " );
    currentTimeTextDrawer.getFontDrawerRef().setPoint( { 600, 550 }, TTextAlignment::leftAlignment );
    currentTimeTextDrawer.isVisible = true;

    TFontDrawer secondsTextDrawer( renderer, fontFile, fontSize + 6 );
    secondsTextDrawer.setText( "0" );
    secondsTextDrawer.getFontDrawerRef().setPoint( { 720, 550 }, TTextAlignment::rightAlignment );
    secondsTextDrawer.isVisible = true;
    
    TDrawer mainDrawer( renderer );
    mainDrawer.addPrimitive( background );
    mainDrawer.addField( &fieldDrawer );
    mainDrawer.addText( &statusTextDrawer );
    mainDrawer.addText( &titleTextDrawer );
    mainDrawer.addText( &flagsCountTextDrawer );
    mainDrawer.addText( &currentTimeTextDrawer );
    mainDrawer.addText( &secondsTextDrawer );

    game.mainDrawer = &mainDrawer;
    game.cellRectangles = &mainFieldCellsGrid;
    game.gameStatus = &statusTextDrawer;
    game.gameTitle = &titleTextDrawer;
    game.flagsCountDrawer = &flagsCountTextDrawer;
    game.timeDrawer = &currentTimeTextDrawer;
    game.secondsDrawer = &secondsTextDrawer;

    thread mainThr1( &TMinesweeperGame::gameThread, &game );

    game.ioThread();

    mainThr1.join();
}
