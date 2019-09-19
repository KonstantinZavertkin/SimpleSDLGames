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

using namespace io_submodule;


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
    cellsFieldParams.xCellsCount = 40;
    cellsFieldParams.yCellsCount = 30;
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
    TCellRectangles gameFieldDrawer;
    gameFieldDrawer.setCellsFieldParams( activeGameField, cellsFieldParams );
    gameFieldDrawer.calcGrid();

    TColorRGB red = { 0xFF, 0x00, 0x00, 0xFF };
    TColorRGB green = { 0x00, 0xFF, 0x00, 0xFF };
    //TColorRGB blue = { 0x00, 0x00, 0xFF, 0xFF };
    //TColorRGB black = { 0x00, 0x00, 0x00, 0xFF };
    TColorRGB white = { 0xFF, 0xFF, 0xFF, 0xFF };
    

    TRectangleDescription tempRect;

    for ( size_t i = 2; i < 12; ++i )
    {
        tempRect = gameFieldDrawer.getCellRectangle( 1, i );
        tempRect.isFilled = true;
        tempRect.color = red;
        drawer.draw( tempRect );
        tempRect.isFilled = false;
        tempRect.color = white;
        drawer.draw( tempRect );
    }

    tempRect = gameFieldDrawer.getCellRectangle( 1, 20 );
    tempRect.isFilled = true;
    tempRect.color = green;
    drawer.draw( tempRect );
    tempRect.isFilled = false;
    tempRect.color = white;
    drawer.draw( tempRect );

    drawer.updateScreen();

    TSurface keyUpBmp( "./resources/up.bmp" );
    TSurface keyDownBmp( "./resources/down.bmp" );
    TSurface keyRightBmp( "./resources/right.bmp" );
    TSurface keyLeftBmp( "./resources/left.bmp" );

    TTexture keyUp( renderer, keyUpBmp );
    TTexture keyDown( renderer, keyDownBmp );
    TTexture keyRight( renderer, keyRightBmp );
    TTexture keyLeft( renderer, keyLeftBmp );

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
                    drawer.draw( keyUp );
                }
                    
                if ( keyValue == SDLK_DOWN || keyValue == SDLK_s )
                {
                    std::cout << "Key DOWN" << std::endl;
                    drawer.draw( keyDown );
                }

                if ( keyValue == SDLK_LEFT || keyValue == SDLK_a )
                {
                    std::cout << "Key LEFT" << std::endl;
                    drawer.draw( keyLeft );
                }

                if ( keyValue == SDLK_RIGHT || keyValue == SDLK_d )
                {
                    std::cout << "Key RIGHT" << std::endl;
                    drawer.draw( keyRight );
                }
            }
        }

        SDL_Delay( 100 );
    }

    TSdlWrapper::deteteInstance();
};
