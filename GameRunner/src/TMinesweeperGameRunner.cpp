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
    cellsFieldParams.yCellsCount = 20;
    cellsFieldParams.cellHeight = 16;
    cellsFieldParams.cellWidth = 16;
}

void TMinesweeperGameRunner::run()
{
    TCellRectangles mainFieldCellsGrid;
    mainFieldCellsGrid.setCellsFieldParams( activeGameField, cellsFieldParams );
    mainFieldCellsGrid.calcGrid();

    TMinesweeperGame game( { cellsFieldParams.xCellsCount, cellsFieldParams.yCellsCount } );

    game.minesweeper.initializeField( cellsFieldParams.xCellsCount, cellsFieldParams.yCellsCount, 40 );

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
        textures[i].setTexturePart( { i * 16, 0 }, { 16, 16 } );
        textures[i].setStartPoint( { i * 20 + 60, 500 } );
    }

    TTexturesFieldDrawer fieldDrawer( game.gameField, renderer, mainFieldCellsGrid );
    fieldDrawer.textures = &textures;
    fieldDrawer.textureSliceSize = { 16, 16 };
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

    TDrawer mainDrawer( renderer );
    mainDrawer.addPrimitive( background );
    mainDrawer.addField( &fieldDrawer );
    mainDrawer.addText( &statusTextDrawer );

    for ( size_t i = 0; i < 16; ++i )
    {
        mainDrawer.addTexture( &textures[i] );
    }

    game.mainDrawer = &mainDrawer;
    game.cellRectangles = &mainFieldCellsGrid;
    game.gameStatus = &statusTextDrawer;

    thread mainThr1( &TMinesweeperGame::gameThread, &game );

    game.ioThread();

    mainThr1.join();
}
