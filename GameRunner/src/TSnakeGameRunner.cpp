#include "TSnakeGameRunner.h"

TSnakeGameRunner::TSnakeGameRunner( TRenderer& rendererVar )
    : renderer( rendererVar )
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

    TSnakeGame snakeGame( { cellsFieldParams.yCellsCount, cellsFieldParams.xCellsCount }, 5 );

    TFieldDrawer snakeDrawer( snakeGame.gameField, renderer, mainFieldCellsGrid );
    snakeDrawer.cellsMapper = snakeCellsMapper;

    TFontTTF ttfTitleTextPrinter( renderer, fontFile, fontSize + 6 );
    ttfTitleTextPrinter.setPoint( { background.width / 2, 10 }, TTextAlignment::centerAlignment );
    TFontDrawer titleTextDrawer( ttfTitleTextPrinter );
    titleTextDrawer.setText( "Snake" );

    TFontTTF ttfScoreTextPrinter( renderer, fontFile, fontSize );
    auto point = make_pair( activeGameField.xStart + ( cellsFieldParams.xCellsCount + 1 ) * cellsFieldParams.cellWidth + 20, gameFieldBound.yStart );
    ttfScoreTextPrinter.setPoint( point, TTextAlignment::leftAlignment );
    TFontDrawer scoreTextDrawer( ttfScoreTextPrinter );

    TDrawer mainDrawer( renderer );
    mainDrawer.addPrimitive( background );
    mainDrawer.addPrimitive( gameFieldBound );
    mainDrawer.addField( &snakeDrawer );
    mainDrawer.addText( &scoreTextDrawer );
    mainDrawer.addText( &titleTextDrawer );

    snakeGame.mainDrawer = &mainDrawer;
    snakeGame.scorePrinter = &scoreTextDrawer;

    thread mainThr( &TSnakeGame::gameThread, &snakeGame );

    snakeGame.ioThread();

    mainThr.join();
}