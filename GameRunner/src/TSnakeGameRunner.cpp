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

    TPrimitivesFieldDrawer snakeDrawer( snakeGame.gameField, renderer, mainFieldCellsGrid );
    snakeDrawer.cellsMapper = snakeCellsMapper;

    TFontDrawer titleTextDrawer( renderer, fontFile, fontSize + 6 );
    titleTextDrawer.getFontDrawerRef().setPoint( { background.width / 2, 10 }, TTextAlignment::centerAlignment );
    titleTextDrawer.setText( "Snake" );

    auto point = make_pair( activeGameField.xStart + ( cellsFieldParams.xCellsCount + 1 ) * cellsFieldParams.cellWidth + 20, gameFieldBound.yStart );
    TFontDrawer scoreTextDrawer( renderer, fontFile, fontSize );
    scoreTextDrawer.getFontDrawerRef().setPoint( point, TTextAlignment::leftAlignment );

    point.second += 50;
    TFontDrawer bestScoreTextDrawer( renderer, fontFile, fontSize );
    bestScoreTextDrawer.getFontDrawerRef().setPoint( point, TTextAlignment::leftAlignment );

    TDrawer mainDrawer( renderer );
    mainDrawer.addPrimitive( background );
    mainDrawer.addPrimitive( gameFieldBound );
    mainDrawer.addField( &snakeDrawer );
    mainDrawer.addText( &scoreTextDrawer );
    mainDrawer.addText( &titleTextDrawer );
    mainDrawer.addText( &bestScoreTextDrawer );

    snakeGame.mainDrawer = &mainDrawer;
    snakeGame.scorePrinter = &scoreTextDrawer;
    snakeGame.bestScorePrinter = &bestScoreTextDrawer;

    thread mainThr( &TSnakeGame::gameThread, &snakeGame );

    snakeGame.ioThread();

    mainThr.join();
}
