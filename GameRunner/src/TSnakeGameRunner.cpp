#include "TSnakeGameRunner.h"

#include "TMainMenu.h"

TSnakeGameRunner::TSnakeGameRunner( TRenderer& rendererVar )
    : IAbstractRunner( rendererVar )
{
}

void TSnakeGameRunner::init()
{
    cellsFieldParams.xCellsCount = 20;
    cellsFieldParams.yCellsCount = 20;
    cellsFieldParams.cellHeight = 25;
    cellsFieldParams.cellWidth = 25;

    gameFieldBound.xStart = activeGameField.xStart - 1;
    gameFieldBound.yStart = activeGameField.yStart - 1;
    gameFieldBound.width = cellsFieldParams.xCellsCount * cellsFieldParams.cellWidth + 2;
    gameFieldBound.height = cellsFieldParams.yCellsCount * cellsFieldParams.cellHeight + 2;
    gameFieldBound.isFilled = false;
    gameFieldBound.color = { 0xFF, 0xFF, 0xFF, 0xFF };
}

void TSnakeGameRunner::run()
{
    TCellRectangles mainFieldCellsGrid;
    mainFieldCellsGrid.setCellsFieldParams( activeGameField, cellsFieldParams );
    mainFieldCellsGrid.calcGrid();

    TSnakeGame gameObject( { cellsFieldParams.yCellsCount, cellsFieldParams.xCellsCount }, 5 );

    TPrimitivesFieldDrawer snakeDrawer( gameObject.snakeBackend.gameField, rendererRef, mainFieldCellsGrid );
    snakeDrawer.cellsMapper = snakeCellsMapper;

    TFontDrawer titleTextDrawer( rendererRef, fontFile, fontSize + 6 );
    titleTextDrawer.setPoint( { background.width / 2, 10 }, TTextAlignment::centerAlignment );
    titleTextDrawer.setText( "Snake" );

    auto point = make_pair( activeGameField.xStart + ( cellsFieldParams.xCellsCount + 1 ) * cellsFieldParams.cellWidth + 20, gameFieldBound.yStart );
    TFontDrawer scoreTextDrawer( rendererRef, fontFile, fontSize );
    scoreTextDrawer.setPoint( point, TTextAlignment::leftAlignment );

    point.second += 50;
    TFontDrawer bestScoreTextDrawer( rendererRef, fontFile, fontSize );
    bestScoreTextDrawer.setPoint( point, TTextAlignment::leftAlignment );

    TDrawer mainDrawer( rendererRef );
    mainDrawer.addPrimitive( background );
    mainDrawer.addPrimitive( gameFieldBound );
    mainDrawer.addField( &snakeDrawer );
    mainDrawer.addText( &scoreTextDrawer );
    mainDrawer.addText( &titleTextDrawer );
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

    gameObject.mainDrawer = &mainDrawer;
    gameObject.scorePrinter = &scoreTextDrawer;
    gameObject.bestScorePrinter = &bestScoreTextDrawer;
    gameObject.pauseMenu = &pauseMenu;

    bool runGame = true;

    while ( runGame )
    {
        thread mainThr( &TSnakeGame::gameThread, &gameObject );

        gameObject.ioThread();
        mainThr.join();

        runGame = false;

        if ( gameObject.snakeBackend.gameOver )
        {
            const auto ans = gameOverMenu.show();

            if ( ans == 0 )
            {
                gameObject.snakeBackend.reset();
                runGame = true;
            }
        }
    }
}
