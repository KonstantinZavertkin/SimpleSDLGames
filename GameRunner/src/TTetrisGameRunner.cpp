#include "TTetrisGameRunner.h"
#include "TMainMenu.h"

TTetrisGameRunner::TTetrisGameRunner( TRenderer& rendererArg )
    : IAbstractRunner( rendererArg )
{
}

void TTetrisGameRunner::init()
{
    cellsFieldParams.xCellsCount = 10;
    cellsFieldParams.yCellsCount = 20;
    cellsFieldParams.cellHeight = 25;
    cellsFieldParams.cellWidth = 25;

    cellsInfoFieldParams.xCellsCount = 4;
    cellsInfoFieldParams.yCellsCount = 4;
    cellsInfoFieldParams.cellHeight = 15;
    cellsInfoFieldParams.cellWidth = 15;

    gameFieldBound.xStart = activeGameField.xStart - 1;
    gameFieldBound.yStart = activeGameField.yStart - 1;
    gameFieldBound.width = cellsFieldParams.xCellsCount * cellsFieldParams.cellWidth + 2;
    gameFieldBound.height = cellsFieldParams.yCellsCount * cellsFieldParams.cellHeight + 2;
    gameFieldBound.isFilled = false;
    gameFieldBound.color = { 0xFF, 0xFF, 0xFF, 0xFF };

    gameInfoField.xStart = activeGameField.xStart + ( cellsFieldParams.xCellsCount + 1 ) * cellsFieldParams.cellWidth + 60;
    gameInfoField.yStart = 120;
    gameInfoField.width = cellsInfoFieldParams.xCellsCount * cellsInfoFieldParams.cellWidth;
    gameInfoField.height = cellsInfoFieldParams.yCellsCount * cellsInfoFieldParams.cellHeight;

    infoFieldBound.xStart = gameInfoField.xStart - 1;
    infoFieldBound.yStart = gameInfoField.yStart - 1;
    infoFieldBound.width = cellsInfoFieldParams.xCellsCount * cellsInfoFieldParams.cellWidth + 2;
    infoFieldBound.height = cellsInfoFieldParams.yCellsCount * cellsInfoFieldParams.cellHeight + 2;
    infoFieldBound.isFilled = false;
    infoFieldBound.color = { 0xFF, 0xFF, 0xFF, 0xFF };
}

void TTetrisGameRunner::run()
{
    TCellRectangles mainFieldCellsGrid;
    mainFieldCellsGrid.setCellsFieldParams( activeGameField, cellsFieldParams );
    mainFieldCellsGrid.calcGrid();

    TCellRectangles infoFieldCellsGrid;
    infoFieldCellsGrid.setCellsFieldParams( gameInfoField, cellsInfoFieldParams );
    infoFieldCellsGrid.calcGrid();

    TTetrisGame tetris( { cellsFieldParams.yCellsCount, cellsFieldParams.xCellsCount } );

    TPrimitivesFieldDrawer tetrisDrawer( tetris.tetrisBackend.gameField, rendererRef, mainFieldCellsGrid );
    tetrisDrawer.cellsMapper = tetrisCellsMapper;

    TPrimitivesFieldDrawer infoFieldDrawer( tetris.tetrisBackend.nextFigureField, rendererRef, infoFieldCellsGrid );
    infoFieldDrawer.cellsMapper = tetrisCellsMapper;

    auto point = make_pair( infoFieldBound.xStart, gameFieldBound.yStart );

    TFontDrawer nextFigureTextDrawer( rendererRef, fontFile, fontSize );
    nextFigureTextDrawer.getFontDrawerRef().setPoint( point, TTextAlignment::leftAlignment );
    nextFigureTextDrawer.setText( "Next figure:" );

    point.second += 180;
    TFontDrawer scoreTextDrawer( rendererRef, fontFile, fontSize );
    scoreTextDrawer.getFontDrawerRef().setPoint( point, TTextAlignment::leftAlignment );

    point.second += 50;
    TFontDrawer bestScoreTextDrawer( rendererRef, fontFile, fontSize );
    bestScoreTextDrawer.getFontDrawerRef().setPoint( point, TTextAlignment::leftAlignment );

    TFontDrawer titleTextDrawer( rendererRef, fontFile, fontSize + 6 );
    titleTextDrawer.getFontDrawerRef().setPoint( { background.width / 2, 10 }, TTextAlignment::centerAlignment );
    titleTextDrawer.setText( "Tetris" ); 
    
    TDrawer mainDrawer( rendererRef );
    mainDrawer.addPrimitive( background );
    mainDrawer.addPrimitive( gameFieldBound );
    mainDrawer.addPrimitive( infoFieldBound );
    mainDrawer.addField( &tetrisDrawer );
    mainDrawer.addField( &infoFieldDrawer );
    mainDrawer.addText( &scoreTextDrawer );
    mainDrawer.addText( &titleTextDrawer );
    mainDrawer.addText( &bestScoreTextDrawer );
    mainDrawer.addText( &nextFigureTextDrawer );

    TMainMenu pauseMenu( rendererRef );
    pauseMenu.background = background;
    pauseMenu.fontSize = fontSize + 10;
    pauseMenu.fontFile = fontFile;
    pauseMenu.generateHorizontalBorders( 200, 260, 2 );
    pauseMenu.addItem( "Resume" );
    pauseMenu.addItem( "Exit" );
    pauseMenu.setUpDrawer();

    TFontDrawer gameOver( rendererRef, fontFile, fontSize + 10 );
    gameOver.getFontDrawerRef().setText( "Game over " );
    gameOver.getFontDrawerRef().setColor( { 0xFF, 0xFF, 00, 0xFF } );
    gameOver.getFontDrawerRef().setPoint( { background.width / 2 - 70, 160 }, TTextAlignment::leftAlignment );

    TMainMenu gameOverMenu( rendererRef );
    gameOverMenu.background = background;
    gameOverMenu.fontSize = fontSize + 10;
    gameOverMenu.fontFile = fontFile;
    gameOverMenu.generateHorizontalBorders( 200, 260, 2 );
    gameOverMenu.addItem( "Retry" );
    gameOverMenu.addItem( "Exit" );
    gameOverMenu.addLabel( std::move( gameOver ) );
    gameOverMenu.setUpDrawer();

    tetris.mainDrawer = &mainDrawer;
    tetris.scorePrinter = &scoreTextDrawer;
    tetris.bestScorePrinter = &bestScoreTextDrawer;
    tetris.pauseMenu = &pauseMenu;

    bool runGame = true;

    while ( runGame )
    {
        thread mainThr( &TTetrisGame::gameThread, &tetris );

        tetris.ioThread();
        mainThr.join();

        runGame = false;

        if ( tetris.tetrisBackend.gameOver )
        {
            const auto ans = gameOverMenu.show();

            if ( ans == 0 )
            {
                tetris.tetrisBackend.reset();
                runGame = true;
            }
        }
    }
}
