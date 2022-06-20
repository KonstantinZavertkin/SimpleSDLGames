#include "TMainMenu.h"

TMainMenu::TMainMenu( TRenderer& rendererRef )
    : renderer( rendererRef )
{
}

size_t TMainMenu::show()
{
    TFontDrawer titleTextDrawer1( renderer, fontFile, fontSize );
    titleTextDrawer1.getFontDrawerRef().setText( "Tetris" );
    titleTextDrawer1.getFontDrawerRef().setPoint( { background.width / 2 - 50, 200 }, TTextAlignment::leftAlignment );

    TFontDrawer cursorDrawer1( renderer, fontFile, fontSize );
    cursorDrawer1.getFontDrawerRef().setText( ">" );
    cursorDrawer1.getFontDrawerRef().setPoint( { background.width / 2 - 70, 200 }, TTextAlignment::leftAlignment );
    cursorDrawer1.getFontDrawerRef().setColor( colorSelected );
    cursorDrawer1.isVisible = false;

    TFontDrawer titleTextDrawer2( renderer, fontFile, fontSize );
    titleTextDrawer2.getFontDrawerRef().setText( "Snake" );
    titleTextDrawer2.getFontDrawerRef().setPoint( { background.width / 2 - 50, 225 }, TTextAlignment::leftAlignment );

    TFontDrawer cursorDrawer2( renderer, fontFile, fontSize );
    cursorDrawer2.getFontDrawerRef().setText( ">" );
    cursorDrawer2.getFontDrawerRef().setPoint( { background.width / 2 - 70, 225 }, TTextAlignment::leftAlignment );
    cursorDrawer2.getFontDrawerRef().setColor( colorSelected );
    cursorDrawer2.isVisible = false;

    TFontDrawer titleTextDrawer3( renderer, fontFile, fontSize );
    titleTextDrawer3.getFontDrawerRef().setText( "Minesweeper" );
    titleTextDrawer3.getFontDrawerRef().setPoint( { background.width / 2 - 50, 250 }, TTextAlignment::leftAlignment );

    TFontDrawer cursorDrawer3( renderer, fontFile, fontSize );
    cursorDrawer3.getFontDrawerRef().setText( ">" );
    cursorDrawer3.getFontDrawerRef().setPoint( { background.width / 2 - 70, 250 }, TTextAlignment::leftAlignment );
    cursorDrawer3.getFontDrawerRef().setColor( colorSelected );
    cursorDrawer3.isVisible = false;

    TFontDrawer titleTextDrawerExit( renderer, fontFile, fontSize );
    titleTextDrawerExit.getFontDrawerRef().setText( "Exit" );
    titleTextDrawerExit.getFontDrawerRef().setPoint( { background.width / 2 - 50, 275 }, TTextAlignment::leftAlignment );

    TFontDrawer cursorDrawerExit( renderer, fontFile, fontSize );
    cursorDrawerExit.getFontDrawerRef().setText( ">" );
    cursorDrawerExit.getFontDrawerRef().setPoint( { background.width / 2 - 70, 275 }, TTextAlignment::leftAlignment );
    cursorDrawerExit.getFontDrawerRef().setColor( colorSelected );
    cursorDrawerExit.isVisible = false;

    textDrivers.push_back( &titleTextDrawer1 );
    textDrivers.push_back( &titleTextDrawer2 );
    textDrivers.push_back( &titleTextDrawer3 );
    textDrivers.push_back( &titleTextDrawerExit );

    cursorDrivers.push_back( &cursorDrawer1 );
    cursorDrivers.push_back( &cursorDrawer2 );
    cursorDrivers.push_back( &cursorDrawer3 );
    cursorDrivers.push_back( &cursorDrawerExit );

    TDrawer mainDrawer( renderer );
    mainDrawer.addText( &titleTextDrawer1 );
    mainDrawer.addText( &titleTextDrawer2 );
    mainDrawer.addText( &titleTextDrawer3 );
    mainDrawer.addText( &titleTextDrawerExit );
    mainDrawer.addText( &cursorDrawer1 );
    mainDrawer.addText( &cursorDrawer2 );
    mainDrawer.addText( &cursorDrawer3 );
    mainDrawer.addText( &cursorDrawerExit );
    mainDrawer.addPrimitive( background );

    textDrivers[currentSelectedItem]->getFontDrawerRef().setColor( colorSelected );
    cursorDrivers[currentSelectedItem]->isVisible = true;

    SDL_Event ioEvent;
    bool quitLocal = false;

    while ( !quitLocal )
    {
        while ( SDL_PollEvent( &ioEvent ) != 0 )
        {
            if ( ioEvent.type == SDL_QUIT )
            {
                quitLocal = true;
                exitFlag = true;
            }

            if ( ioEvent.type == SDL_KEYDOWN )
            {
                auto keyValue = ioEvent.key.keysym.sym;

                for ( auto ptrToDrawer: cursorDrivers )
                   ptrToDrawer->isVisible = false;

                for ( auto ptrToDrawer: textDrivers )
                   ptrToDrawer->getFontDrawerRef().setColor( defaultColor );

                if ( keyValue == SDLK_DOWN )
                   ++currentSelectedItem;

                if ( keyValue == SDLK_UP )
                {
                    if ( currentSelectedItem != 0 )
                        --currentSelectedItem;
                    else
                       currentSelectedItem = itemsCount - 1;
                }

                if ( keyValue == SDLK_RETURN )
                   quitLocal = true;
                   
                currentSelectedItem %= itemsCount;

                textDrivers[currentSelectedItem]->getFontDrawerRef().setColor( colorSelected );
                cursorDrivers[currentSelectedItem]->isVisible = true;
            }
        }

        mainDrawer.draw();

        SDL_Delay( 1 );
    }

    if ( currentSelectedItem == itemsCount - 1 )
       exitFlag = true;

    if ( exitFlag )
       return itemsCount;

    return currentSelectedItem;
}

bool TMainMenu::exitEvent() const
{
    return exitFlag;
}
