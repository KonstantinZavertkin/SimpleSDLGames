#include <stdlib.h>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <functional>

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
#include "TSnake.h"

#include "TFieldDrawer.h"

using namespace io_submodule;
using namespace game_backend;

int main()
{
    TSdlWrapper::getInstance();

    //! Main window params
    size_t wholeWidth = 640;
    size_t wholeHeight = 480;
    size_t xStartBias = 10;
    size_t yStartBias = 40;
    size_t activeGameFieldWidth = wholeWidth - xStartBias * 2;
    size_t activeGameFieldHeight = wholeHeight - yStartBias - 10;
    
    //! Main window params
    TRectangleDescription mainWindowParams;
    mainWindowParams.width = wholeWidth;
    mainWindowParams.height = wholeHeight;
    mainWindowParams.isFilled = true;
    mainWindowParams.color = { 0, 0, 0, 0xFF };

    //! Area for cells
    TRectangleDescription activeGameField;
    activeGameField.xStart = xStartBias;
    activeGameField.yStart = yStartBias;
    activeGameField.width = activeGameFieldWidth;
    activeGameField.height = activeGameFieldHeight;
    activeGameField.color = { 0, 0, 0, 0xFF };
    activeGameField.isFilled = true;

    //! Border around area for cells
    TRectangleDescription gameFieldBound = activeGameField;
    gameFieldBound.xStart -= 1;
    gameFieldBound.yStart -= 1;
    gameFieldBound.width += 1;
    gameFieldBound.height += 1;
    gameFieldBound.isFilled = false;
    gameFieldBound.color = { 0xFF, 0xFF, 0xFF, 0xFF };

    //! Cells params
    TCellsFieldParams cellsFieldParams;
    cellsFieldParams.xCellsCount = 30;
    cellsFieldParams.yCellsCount = 20;
    cellsFieldParams.cellHeight = 20;
    cellsFieldParams.cellWidth = 20;
    
    //! Create window, renderer and drawer
    TWindow wnd( "Main", mainWindowParams );
    TRenderer renderer( wnd );
    TDrawer drawer( renderer );

    //! Draw static objects
    drawer.draw( mainWindowParams );
    drawer.draw( activeGameField );
    drawer.draw( gameFieldBound );

    //! Calc cells coordinates
    //! Mapping (xCell, yCell) to (xWindow, yWindow)
    //! where [x|y]Cell - cells coordinate in 2d array of cells
    //! [x|y]Window - cells coordinate in pixels for corresponding window
    TCellRectangles cellRectangles;
    cellRectangles.setCellsFieldParams( activeGameField, cellsFieldParams );
    cellRectangles.calcGrid();

    //! Game backend
    TGameField gameField( cellsFieldParams.yCellsCount, cellsFieldParams.xCellsCount );
    TSnake snake( gameField );
    pair<size_t, size_t> start = { 1, 1 };
    snake.initSnake( start, 12 );

    TFieldDrawer fDrawer( gameField, drawer, cellRectangles );

    // Main loop
    bool quit = false;
    SDL_Event exitEvent;

    while ( !quit )
    {
        while ( SDL_PollEvent( &exitEvent ) != 0 )
        {
            if ( exitEvent.type == SDL_QUIT )
                quit = true;

            if ( exitEvent.type == SDL_KEYDOWN )
            {
                auto keyValue = exitEvent.key.keysym.sym;

                if ( keyValue == SDLK_UP || keyValue == SDLK_w )
                {
                    std::cout << "Key UP" << std::endl;
                    snake.turn( { -1, 0 } );
                }
                    
                if ( keyValue == SDLK_DOWN || keyValue == SDLK_s )
                {
                    std::cout << "Key DOWN" << std::endl;
                    snake.turn( { 1, 0 } );
                }

                if ( keyValue == SDLK_LEFT || keyValue == SDLK_a )
                {
                    std::cout << "Key LEFT" << std::endl;
                    snake.turn( { 0, -1 } );
                }

                if ( keyValue == SDLK_RIGHT || keyValue == SDLK_d )
                {
                    std::cout << "Key RIGHT" << std::endl;
                    snake.turn( { 0, 1 } );
                }
            }
        }

        snake.step();
        fDrawer.draw();
        drawer.updateScreen();
        SDL_Delay( 350 );
        //std::cout << "." << endl;
    }

    //std::cout << std::endl;

    TSdlWrapper::deteteInstance();
};
