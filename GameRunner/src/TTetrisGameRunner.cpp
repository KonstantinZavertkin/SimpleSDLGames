#include "TTetrisGameRunner.h"

TTetrisGameRunner::TTetrisGameRunner( TRenderer& rendererArg )
    : renderer( rendererArg )
{
}

void TTetrisGameRunner::init()
{
    gameFieldBound.xStart = activeGameField.xStart - 1;
    gameFieldBound.yStart = activeGameField.yStart - 1;
    gameFieldBound.width = cellsFieldParams.xCellsCount * cellsFieldParams.cellWidth + 2;
    gameFieldBound.height = cellsFieldParams.yCellsCount * cellsFieldParams.cellHeight + 2;
    gameFieldBound.isFilled = false;
    gameFieldBound.color = { 0xFF, 0xFF, 0xFF, 0xFF };

    gameInfoField.xStart = activeGameField.xStart + ( cellsFieldParams.xCellsCount + 1 ) * cellsFieldParams.cellWidth + 20;
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

    TFieldDrawer tetrisDrawer( tetris.tetrisBackend.gameField, renderer, mainFieldCellsGrid );
    tetrisDrawer.cellsMapper = tetrisCellsMapper;
    tetrisDrawer.addStaticPrimitiveLast( gameFieldBound );

    TFieldDrawer infoFieldDrawer( tetris.tetrisBackend.nextFigureField, renderer, infoFieldCellsGrid );
    infoFieldDrawer.cellsMapper = tetrisCellsMapper;
    infoFieldDrawer.addStaticPrimitiveLast( infoFieldBound );

    TFontTTF ttfScoreTextPrinter( renderer, fontFile, fontSize );
    auto point = make_pair( activeGameField.xStart + ( cellsFieldParams.xCellsCount + 1 ) * cellsFieldParams.cellWidth + 20, gameFieldBound.yStart );
    ttfScoreTextPrinter.setPoint( point, TTextAlignment::leftAlignment );
    TFontDrawer scoreTextDrawer( ttfScoreTextPrinter );

    TFontTTF ttfTitleTextPrinter( renderer, fontFile, fontSize +6);
    ttfTitleTextPrinter.setText( "Tetris" );
    ttfTitleTextPrinter.setPoint( { background.width / 2, 10 }, TTextAlignment::centerAlignment );
    TFontDrawer titleTextDrawer( ttfTitleTextPrinter );
    
    TDrawer mainDrawer( renderer );
    mainDrawer.addPrimitive( background );
    mainDrawer.addPrimitive( gameFieldBound );
    mainDrawer.addPrimitive( infoFieldBound );
    mainDrawer.addField( &tetrisDrawer );
    mainDrawer.addField( &infoFieldDrawer );
    mainDrawer.addText( &scoreTextDrawer );
    mainDrawer.addText( &titleTextDrawer );

    tetris.mainDrawer = &mainDrawer;
    tetris.scorePrinter = &scoreTextDrawer;

    thread mainThr2( &TTetrisGame::gameThread, &tetris );

    tetris.ioThread();

    mainThr2.join();
}
