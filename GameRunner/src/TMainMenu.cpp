#include "TMainMenu.h"

TMainMenu::TMainMenu( TRenderer& rendererRef )
    : renderer( rendererRef )
{
}

void TMainMenu::show()
{
    TFontDrawer titleTextDrawer1( renderer, fontFile, fontSize );
    titleTextDrawer1.getFontDrawerRef().setText( "Tetris" );
    titleTextDrawer1.getFontDrawerRef().setPoint( { background.width / 2 - 50, 220 }, TTextAlignment::leftAlignment );

    TFontDrawer titleTextDrawer2( renderer, fontFile, fontSize );
    titleTextDrawer2.getFontDrawerRef().setText( "Snake" );
    titleTextDrawer2.getFontDrawerRef().setPoint( { background.width / 2 - 50, 240 }, TTextAlignment::leftAlignment );

    TFontDrawer titleTextDrawer3( renderer, fontFile, fontSize );
    titleTextDrawer3.getFontDrawerRef().setText( "Exit" );
    titleTextDrawer3.getFontDrawerRef().setPoint( { background.width / 2 - 50, 260 }, TTextAlignment::leftAlignment );

    TDrawer mainDrawer( renderer );
    mainDrawer.addText( &titleTextDrawer1 );
    mainDrawer.addText( &titleTextDrawer2 );
    mainDrawer.addText( &titleTextDrawer3 );

    SDL_Event ioEvent;
    bool pauseLocal = false;
    bool quitLocal = false;

    while ( !quitLocal )
    {
        while ( SDL_PollEvent( &ioEvent ) != 0 )
        {
            if ( ioEvent.type == SDL_QUIT )
            {
                quitLocal = true;
            }

            if ( ioEvent.type == SDL_KEYDOWN )
            {
                
                titleTextDrawer1.getFontDrawerRef().setColor( colorSelected );
                cout << "Key pushed 2" << endl;
            }
        }

        mainDrawer.getRendererRef().resetScreen();
        mainDrawer.draw();
        mainDrawer.getRendererRef().updateScreen();

        SDL_Delay( 1 );
    }
}
