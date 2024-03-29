#include <iostream>
#include <string>
#include "sdl2_include.h"

#include "TWindow.h"
#include "TSdlWrapper.h"

#include "TTetrisGameRunner.h"
#include "TSnakeGameRunner.h"
#include "TMainMenu.h"

#include "TMinesweeperBackend.h"
#include "TMinesweeperGameRunner.h"

using namespace io_submodule;
using namespace game_backend;

int main( int argc, char **argv )
{
    std::srand( time( 0 ) );
    TSdlWrapper initSDL2;

    //! Main window params
    size_t wholeWidth = 800;
    size_t wholeHeight = 600;
    size_t xStartBias = 50;
    size_t yStartBias = 50;

    string fontFile = "./resources/font/font.ttf";
    int fontSize = 22;
    
    TRectangleDescription background;
    background.xStart = 0;
    background.yStart = 0;
    background.width = wholeWidth;
    background.height = wholeHeight;
    background.isFilled = true;
    background.color = { 0, 0, 0, 0xFF };

    //! Create window, renderer and renderer
    TWindow wnd( "SimpleSDL2Games", background );
    TRenderer renderer( wnd );

    //! Area for main field
    TRectangleDescription activeGameField;
    activeGameField.isFilled = false;
    activeGameField.xStart = xStartBias;
    activeGameField.yStart = yStartBias;

    TMainMenu menu( renderer );
    menu.background = background;
    menu.fontSize = fontSize + 10;
    menu.fontFile = fontFile;

    menu.initGridParams( 200, 30 );
    menu.addExtendedCursor( "Select game:  " );
    menu.addItem( "Minesweeper" );
    menu.addItem( "Tetris" );
    menu.addItem( "Snake" );
    menu.addItem( "Exit" );
    menu.setUp();

    while ( !menu.exitEvent() )
    {
        const auto selectedItem = menu.show();
        unique_ptr<IAbstractRunner> gameRunner = nullptr;

        if ( selectedItem == 0 )
            gameRunner = make_unique<TMinesweeperGameRunner>( renderer );

        if ( selectedItem == 1 )
            gameRunner = make_unique<TTetrisGameRunner>( renderer );

        if ( selectedItem == 2 )
            gameRunner = make_unique<TSnakeGameRunner>( renderer );

        if ( gameRunner )
        {
            gameRunner->activeGameField = activeGameField;
            gameRunner->background = background;

            gameRunner->fontFile = fontFile;
            gameRunner->fontSize = fontSize;

            gameRunner->init();
            gameRunner->run();
        }
    }

    return 0;
};
