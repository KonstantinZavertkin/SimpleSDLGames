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

void runTetrisNew( TRenderer& renderer, TRectangleDescription& activeGameField, TRectangleDescription& background, const string& fontFile, size_t fontSize )
{
    TTetrisGameRunner game( renderer );

    game.activeGameField = activeGameField;
    game.background = background;

    game.fontFile = fontFile;
    game.fontSize = fontSize;

    game.init();
    game.run();
};

void runSnakeNew( TRenderer& renderer, TRectangleDescription& activeGameField, TRectangleDescription& background, const string& fontFile, size_t fontSize )
{
    TSnakeGameRunner game( renderer );

    game.activeGameField = activeGameField;
    game.background = background;

    game.fontFile = fontFile;
    game.fontSize = fontSize;

    game.init();
    game.run();
};

void runMinesweeper( TRenderer& renderer, TRectangleDescription& activeGameField, TRectangleDescription& background, const string& fontFile, size_t fontSize )
{
    TMinesweeperGameRunner game( renderer );

    game.activeGameField = activeGameField;
    game.background = background;

    game.fontFile = fontFile;
    game.fontSize = fontSize;

    game.init();
    game.run();
}

int main( int argc, char **argv )
{
    //std::srand( time( 0 ) );
    TSdlWrapper::getInstance();

    //! Main window params
    size_t wholeWidth = 800;
    size_t wholeHeight = 600;
    size_t xStartBias = 50;
    size_t yStartBias = 50;

    string fontFile = "Samson.ttf";
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
    TWindow wnd( "Main", background );
    TRenderer renderer( wnd );

    //! Area for main field
    TRectangleDescription activeGameField;
    activeGameField.isFilled = false;
    activeGameField.xStart = xStartBias;
    activeGameField.yStart = yStartBias;

    TMainMenu menu( renderer );
    menu.background = background;
    menu.fontSize = fontSize;
    menu.fontFile = fontFile;

    //---------------------
    /*
   TMinesweeperBackend minesweeper;
   minesweeper.initializeField( 20, 20, 40 );
   Field& field = minesweeper.getField();
   
   for( int i = 0; i < 20; i++ )
   {
      cout << "| ";
      for( int j = 0; j < 20; j++ )
      {
         if( field.isFlag( j, i ) )
         {
            cout << 'f' << ' ';
         }
         else
         {
            if( field.isBomb( j, i ) )
            {
               cout << 'x' << ' ';
            }
            else
            {
               cout << field.getValue( j, i ) << ' ';
            }
         }
      }
      cout << "|" << endl;
   }
   cout << endl;

    minesweeper.performStep(0, 0, 'q');
   field = minesweeper.getField();

     minesweeper.performStep(18, 6, 'q');
    field = minesweeper.getField();
   

    //==================================
    for( int i = 0; i < 20; i++ )
   {
      cout << "|";
      for( int j = 0; j < 20; j++ )
      {
         if( field.isFlag( j, i ) )
         {
            cout << 'f' << '|';
         }
         else
         {
            if( field.isOpened( j, i ) )
            {
               cout << field.getValue( j, i ) << '|';
            }
            else
            {
               cout << '_' << '|';
            }
         }
      }
      cout << endl;
   }
   cout << endl;*/

    //---------------------

    while ( !menu.exitEvent() )
    {
        const auto selectedItem = menu.show();

        if ( selectedItem == 0 )
        {
            activeGameField.xStart = 200;
            runTetrisNew( renderer, activeGameField, background, fontFile, fontSize );
        }

        if ( selectedItem == 1 )
        {
            activeGameField.xStart = xStartBias;
            runSnakeNew( renderer, activeGameField, background, fontFile, fontSize );
        }

        if ( selectedItem == 2 )
        {
            activeGameField.xStart = xStartBias;
            runMinesweeper( renderer, activeGameField, background, fontFile, fontSize );
        }
    }
    
    TSdlWrapper::deteteInstance();

    return 0;
};
