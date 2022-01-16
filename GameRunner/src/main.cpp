#include <stdlib.h>
#include <iostream>
#include <string>
#include <functional>
#include <thread>
#include "sdl2_include.h"

#include "TWindow.h"
#include "TSdlWrapper.h"
#include "TRenderer.h"
#include "TSurface.h"
#include "TTexture.h"
#include "TDrawer.h"
#include "TParams.h"
#include "TCellRectangles.h"
#include "TCell.h"
#include "TGameField.h"
#include "TCellsChain.h"
#include "TSnakeGame.h"
#include "TFieldDrawer.h"
#include "TFontTTF.h"
#include "TFontDrawer.h"

#include "TTetrisGame.h"

#include "CommonTypes.hpp"

using namespace io_submodule;
using namespace game_backend;

int main( int argc, char **argv )
{
    std::srand( time( 0 ) );
    TSdlWrapper::getInstance();

    //! Main window params
    size_t wholeWidth = 640;
    size_t wholeHeight = 480;
    size_t xStartBias = 10;
    size_t yStartBias = 50;
    size_t activeGameFieldWidth = wholeWidth - xStartBias * 2;
    size_t activeGameFieldHeight = wholeHeight - yStartBias - 10;

    //string fontFile = "C:/git/SnakeGame/resources/font/Samson.ttf";
    string fontFile = "C:/git/SnakeGame/build/Samson.ttf";
    int fontSize = 20;
    
    //! Main window params
    TRectangleDescription mainWindowParams;
    mainWindowParams.width = wholeWidth;
    mainWindowParams.height = wholeHeight;
    mainWindowParams.isFilled = true;
    mainWindowParams.color = { 0, 0, 0, 0xFF };

    //! Cells params
    TCellsFieldParams cellsFieldParams;
    cellsFieldParams.xCellsCount = 10;
    cellsFieldParams.yCellsCount = 20;
    cellsFieldParams.cellHeight = 20;
    cellsFieldParams.cellWidth = 20;

    TCellsFieldParams cellsInfoFieldParams;
    cellsInfoFieldParams.xCellsCount = 4;
    cellsInfoFieldParams.yCellsCount = 4;
    cellsInfoFieldParams.cellHeight = 15;
    cellsInfoFieldParams.cellWidth = 15;

    //! Area for main field
    TRectangleDescription activeGameField;
    activeGameField.xStart = xStartBias;
    activeGameField.yStart = yStartBias;
    activeGameField.width = activeGameFieldWidth;
    activeGameField.height = activeGameFieldHeight;
    activeGameField.color = { 0, 0, 0, 0xFF };
    activeGameField.isFilled = true;

    //! Area for main field
    TRectangleDescription gameInfoField;
    gameInfoField.xStart = activeGameField.xStart + ( cellsFieldParams.xCellsCount + 1 ) * cellsFieldParams.cellWidth + 20;
    gameInfoField.yStart = 100;
    gameInfoField.width = cellsInfoFieldParams.xCellsCount * cellsInfoFieldParams.cellWidth;
    gameInfoField.height = cellsInfoFieldParams.yCellsCount * cellsInfoFieldParams.cellHeight;

    //! Border around the main area
    TRectangleDescription gameFieldBound;
    gameFieldBound.xStart = activeGameField.xStart - 1;
    gameFieldBound.yStart = activeGameField.yStart - 1;
    gameFieldBound.width = cellsFieldParams.xCellsCount * cellsFieldParams.cellWidth + 2;
    gameFieldBound.height = cellsFieldParams.yCellsCount * cellsFieldParams.cellHeight + 2;
    gameFieldBound.isFilled = false;
    gameFieldBound.color = { 0xFF, 0xFF, 0xFF, 0xFF };

    //! Border around the info area
    TRectangleDescription infoFieldBound;
    infoFieldBound.xStart = gameInfoField.xStart - 1;
    infoFieldBound.yStart = gameInfoField.yStart - 1;
    infoFieldBound.width = cellsInfoFieldParams.xCellsCount * cellsInfoFieldParams.cellWidth + 2;
    infoFieldBound.height = cellsInfoFieldParams.yCellsCount * cellsInfoFieldParams.cellHeight + 2;
    infoFieldBound.isFilled = false;
    infoFieldBound.color = { 0xFF, 0xFF, 0xFF, 0xFF };

    //! Debug screen
    TRectangleDescription debugGameField;
    debugGameField.xStart = 320;
    debugGameField.yStart = yStartBias;
    debugGameField.width = activeGameFieldWidth / 2;
    debugGameField.height = activeGameFieldHeight;
    debugGameField.color = { 0, 0, 0, 0xFF };
    debugGameField.isFilled = true;

    TRectangleDescription debugFieldBound;
    debugFieldBound.xStart = debugGameField.xStart - 1;
    debugFieldBound.yStart = debugGameField.yStart - 1;
    debugFieldBound.width = cellsFieldParams.xCellsCount * cellsFieldParams.cellWidth + 2;
    debugFieldBound.height = cellsFieldParams.yCellsCount * cellsFieldParams.cellHeight + 2;
    debugFieldBound.isFilled = false;
    debugFieldBound.color = { 0xFF, 0xFF, 0xFF, 0xFF };

    //! Create window, drawer and drawer
    TWindow wnd( "Main", mainWindowParams );
    TRenderer renderer( wnd );

    //! Draw static objects
    //drawer.draw( mainWindowParams );
    //drawer.draw( activeGameField );
    //drawer.draw( gameFieldBound );

    //drawer.draw( debugGameField );
    //drawer.draw( debugFieldBound );

    //! Calc cells coordinates
    //! Mapping (xCell, yCell) to (xWindow, yWindow)
    //! where [x|y]Cell - cells coordinate in 2d array of cells
    //! [x|y]Window - cells coordinate in pixels for corresponding window
    TCellRectangles mainFieldCellsGrid;
    mainFieldCellsGrid.setCellsFieldParams( activeGameField, cellsFieldParams );
    mainFieldCellsGrid.calcGrid();

    TCellRectangles infoFieldCellsGrid;
    infoFieldCellsGrid.setCellsFieldParams( gameInfoField, cellsInfoFieldParams );
    infoFieldCellsGrid.calcGrid();

    //! Game backend
    /*TSnakeGame snakeGame( { cellsFieldParams.yCellsCount, cellsFieldParams.xCellsCount }, 5 );

    TFieldDrawer snakeDrawer( snakeGame.gameField, drawer, cellRectangles );
    snakeDrawer.addStaticPrimitive( gameFieldBound );

    snakeGame.mainFieldDrawer = &snakeDrawer;

    thread mainThr( &TSnakeGame::gameThread, &snakeGame );

    snakeGame.ioThread();

    mainThr.join();*/

    TTetrisGame tetris( { cellsFieldParams.yCellsCount, cellsFieldParams.xCellsCount } );

    TFieldDrawer tetrisDrawer( tetris.tetrisBackend.gameField, renderer, mainFieldCellsGrid );
    tetrisDrawer.cellsMapper = tetrisCellsMapper;
    tetrisDrawer.addStaticPrimitive( gameFieldBound );

    TFieldDrawer infoFieldDrawer( tetris.tetrisBackend.nextFigureField, renderer, infoFieldCellsGrid );
    infoFieldDrawer.cellsMapper = tetrisCellsMapper;
    infoFieldDrawer.addStaticPrimitive( infoFieldBound );

    TFontTTF ttfTextPrinter( renderer, fontFile, fontSize );
    auto point = make_pair( gameFieldBound.xStart + gameFieldBound.width + 20, gameFieldBound.yStart );
    ttfTextPrinter.setPoint( point );
    TFontDrawer textDrawer( ttfTextPrinter );

    tetris.mainFieldDrawer = &tetrisDrawer;
    tetris.nextFigureFieldDrawer = &infoFieldDrawer;
    tetris.scorePrinter = &textDrawer;

    thread mainThr2( &TTetrisGame::gameThread, &tetris );

    tetris.ioThread();

    mainThr2.join();

    TSdlWrapper::deteteInstance();

    return 0;
};
