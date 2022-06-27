#include <thread>

#include "TMinesweeperGameRunner.h"
#include "TMinesweeperGame.h"
#include "TFieldDrawer.h"
#include "TMainMenu.h"

using namespace std;

TMinesweeperGameRunner::TMinesweeperGameRunner( TRenderer& rendererRef )
    : IAbstractRunner( rendererRef )
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

    TMinesweeperGame gameObject( { cellsFieldParams.yCellsCount, cellsFieldParams.xCellsCount  } );

    //gameObject.minesweeper.initializeField( cellsFieldParams.yCellsCount, cellsFieldParams.xCellsCount, 40 );

    vector<TSurface> surfaces;
    vector<TTexture> textures;

    for ( size_t i = 0; i < 16; ++i )
    {
        surfaces.emplace_back( "./resources/minesweeper_sprites.bmp" );
        textures.emplace_back( rendererRef );
    }

    for ( size_t i = 0; i < 16; ++i )
    {
        textures[i].updateSurface( surfaces[i] );
        textures[i].setTexturePart( { i * 32, 0 }, { 32, 32 } );
        textures[i].setStartPoint( { i * 20 + 60, 500 } );
    }

    TTexturesFieldDrawer fieldDrawer( gameObject.gameField, rendererRef, mainFieldCellsGrid );
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

    TFontDrawer statusTextDrawer( rendererRef, fontFile, fontSize );
    statusTextDrawer.setPoint( { 75, 550 }, TTextAlignment::leftAlignment );
    statusTextDrawer.setText( "Uninitialized" );
    statusTextDrawer.isVisible = false;

    TFontDrawer titleTextDrawer( rendererRef, fontFile, fontSize + 10 );
    titleTextDrawer.setText( "Minesweeper" );
    titleTextDrawer.setPoint( { 400, 10 }, TTextAlignment::centerAlignment );
    titleTextDrawer.isVisible = true;

    TFontDrawer flagsCountTextDrawer( rendererRef, fontFile, fontSize );
    flagsCountTextDrawer.setText( "Flags: " );
    flagsCountTextDrawer.setPoint( { 75, 550 }, TTextAlignment::leftAlignment );
    flagsCountTextDrawer.isVisible = true;

    TFontDrawer currentTimeTextDrawer( rendererRef, fontFile, fontSize );
    currentTimeTextDrawer.setText( "Time: " );
    currentTimeTextDrawer.setPoint( { 600, 550 }, TTextAlignment::leftAlignment );
    currentTimeTextDrawer.isVisible = true;

    TFontDrawer secondsTextDrawer( rendererRef, fontFile, fontSize );
    secondsTextDrawer.setText( "0" );
    secondsTextDrawer.setPoint( { 720, 550 }, TTextAlignment::rightAlignment );
    secondsTextDrawer.isVisible = true;

    TFontDrawer bestScoreTextDrawer( rendererRef, fontFile, fontSize );
    bestScoreTextDrawer.setText( "Best time: " );
    bestScoreTextDrawer.setPoint( { 350, 550 }, TTextAlignment::leftAlignment );
    
    TDrawer mainDrawer( rendererRef );
    mainDrawer.addPrimitive( background );
    mainDrawer.addField( &fieldDrawer );
    mainDrawer.addText( &statusTextDrawer );
    mainDrawer.addText( &titleTextDrawer );
    mainDrawer.addText( &flagsCountTextDrawer );
    mainDrawer.addText( &currentTimeTextDrawer );
    mainDrawer.addText( &secondsTextDrawer );
    mainDrawer.addText( &bestScoreTextDrawer );

    TMainMenu pauseMenu( rendererRef );
    pauseMenu.background = background;
    pauseMenu.fontSize = fontSize + 10;
    pauseMenu.fontFile = fontFile;
    pauseMenu.initGridParams( 200, 30 );
    pauseMenu.addLabelUnderItems( "Pause" );
    pauseMenu.addItem( "Resume" );
    pauseMenu.addItem( "Exit" );
    pauseMenu.setUp();

    TFontDrawer gameOver( rendererRef, fontFile, fontSize + 10 );
    gameOver.setText( "Game over " );
    gameOver.setColor( { 0xFF, 0xFF, 00, 0xFF } );
    gameOver.setPoint( { background.width / 2 - 70, 160 }, TTextAlignment::leftAlignment );

    TMainMenu gameOverMenu( rendererRef );
    gameOverMenu.background = background;
    gameOverMenu.fontSize = fontSize + 10;
    gameOverMenu.fontFile = fontFile;
    gameOverMenu.initGridParams( 200, 30 );
    gameOverMenu.addItem( "Retry" );
    gameOverMenu.addItem( "Exit" );
    gameOverMenu.addLabel( std::move( gameOver ) );
    gameOverMenu.setUp();

    vector<string> items = { "40", "60", "80", "Exit" };

    TFontDrawer startMenuCaption( rendererRef, fontFile, fontSize + 10 );
    startMenuCaption.setText( "Select bombs count:" );
    startMenuCaption.setColor( { 0xFF, 0xFF, 00, 0xFF } );
    startMenuCaption.setPoint( { background.width / 2 - 70, 160 }, TTextAlignment::leftAlignment );

    TMainMenu startMenu( rendererRef );
    startMenu.background = background;
    startMenu.fontSize = fontSize + 10;
    startMenu.fontFile = fontFile;
    startMenu.initGridParams( 200, 30 );

    for ( const auto& item : items )
       startMenu.addItem( item );

    startMenu.addLabel( std::move( startMenuCaption ) );
    startMenu.setUp();

    gameObject.mainDrawer = &mainDrawer;
    gameObject.cellRectangles = &mainFieldCellsGrid;
    gameObject.gameStatus = &statusTextDrawer;
    gameObject.gameTitle = &titleTextDrawer;
    gameObject.flagsCountDrawer = &flagsCountTextDrawer;
    gameObject.timeDrawer = &currentTimeTextDrawer;
    gameObject.secondsDrawer = &secondsTextDrawer;
    gameObject.bestTimeDrawer = &bestScoreTextDrawer;
    gameObject.pauseMenu = &pauseMenu;

    bool runGame = true;

    while ( runGame )
    {
        const auto itemValue = startMenu.show();

        if ( itemValue < items.size() )
        {
            const auto bombsCount = std::stoi( items[itemValue] );
            gameObject.minesweeper.initializeField( cellsFieldParams.yCellsCount, cellsFieldParams.xCellsCount, bombsCount );

            thread mainThr( &TMinesweeperGame::gameThread, &gameObject );

            gameObject.ioThread();
            mainThr.join();

            runGame = false;

            if ( gameObject.minesweeper.isGameOver() )
            {
                const auto ans = gameOverMenu.show();

                if ( ans == 0 )
                {
                    gameObject.minesweeper.initializeField( cellsFieldParams.yCellsCount, cellsFieldParams.xCellsCount, 40 );
                    runGame = true;
                }
            }
        }
        else
           runGame = false;
    }
}
