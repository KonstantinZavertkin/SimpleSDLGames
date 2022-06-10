#include "TMainMenu.h"

TMainMenu::TMainMenu( TRenderer& rendererRef )
    : renderer( rendererRef )
{
}

void TMainMenu::show()
{
    TFontTTF ttfTitleTextPrinter1( renderer, fontFile, fontSize );
    ttfTitleTextPrinter1.setText( "Tetris" );
    ttfTitleTextPrinter1.setPoint( { background.width / 2 - 50, 220 }, TTextAlignment::leftAlignment );
    TFontDrawer titleTextDrawer1( ttfTitleTextPrinter1 );

    TFontTTF ttfTitleTextPrinter2( renderer, fontFile, fontSize );
    ttfTitleTextPrinter2.setText( "Snake" );
    ttfTitleTextPrinter2.setPoint( { background.width / 2 - 50, 240 }, TTextAlignment::leftAlignment );
    TFontDrawer titleTextDrawer2( ttfTitleTextPrinter2 );

    TFontTTF ttfTitleTextPrinter3( renderer, fontFile, fontSize );
    ttfTitleTextPrinter3.setText( "Exit" );
    ttfTitleTextPrinter3.setPoint( { background.width / 2 - 50, 260 }, TTextAlignment::leftAlignment );
    TFontDrawer titleTextDrawer3( ttfTitleTextPrinter3 );

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
                TColorRGB color = { 0xFF, 0x00, 0xFF, 0xFF };
                ttfTitleTextPrinter1.setColor( color );
                cout << "Key pushed 2" << endl;
            }
        }

        mainDrawer.getRendererRef().resetScreen();
        mainDrawer.draw();
        mainDrawer.getRendererRef().updateScreen();

        SDL_Delay( 1 );
    }
}
