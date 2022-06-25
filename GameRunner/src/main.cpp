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
    //std::srand( time( 0 ) );
    TSdlWrapper initSDL2;

    //! Main window params
    size_t wholeWidth = 800;
    size_t wholeHeight = 600;
    size_t xStartBias = 50;
    size_t yStartBias = 50;

    string fontFile = "./resources/font/Samson.ttf";
    int fontSize = 22;
    
    //! Main window params

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

    TFontDrawer title( renderer, fontFile, fontSize + 10 );
    title.getFontDrawerRef().setText( "Select game:" );
    title.getFontDrawerRef().setColor( { 0xFF, 0xFF, 00, 0xFF } );
    title.getFontDrawerRef().setPoint( { 140, 200 }, TTextAlignment::leftAlignment );

    menu.addLabel( std::move( title ) );

    menu.generateHorizontalBorders( 200, 300, 4 );

    menu.addItem( "Minesweeper" );
    menu.addItem( "Tetris" );
    menu.addItem( "Snake" );
    menu.addItem( "Exit" );
    menu.setUpDrawer();

    while ( !menu.exitEvent() )
    {
        const auto selectedItem = menu.show();
        unique_ptr<IAbstractRunner> gameRunner = nullptr;

        if ( selectedItem == 0 )
        {
            activeGameField.xStart = 75;
            gameRunner = make_unique<TMinesweeperGameRunner>( renderer );
        }

        if ( selectedItem == 1 )
        {
            activeGameField.xStart = 200;
            gameRunner = make_unique<TTetrisGameRunner>( renderer );
        }

        if ( selectedItem == 2 )
        {
            activeGameField.xStart = xStartBias;
            gameRunner = make_unique<TSnakeGameRunner>( renderer );
        }

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
