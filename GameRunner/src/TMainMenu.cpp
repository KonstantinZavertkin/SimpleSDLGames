#include "TMainMenu.h"

TMainMenu::TMainMenu( TRenderer& rendererRef )
    : renderer( rendererRef )
{
}

size_t TMainMenu::show()
{
    const size_t horizontalBordersSize = horizontalBorders.size();

    auto horizontalFocus = [this, &horizontalBordersSize]( size_t yCoord )
    {
        auto result = -1;

        for ( int i = 1; i < horizontalBordersSize; ++i )
           if ( yCoord > horizontalBorders[i - 1] && yCoord < horizontalBorders[i])
              result = i - 1;

        return result;
    };

    index = 0;

    TDrawer mainDrawer( renderer );
    mainDrawer.addText( &textDriversNew[index++] );
    mainDrawer.addText( &textDriversNew[index++] );
    mainDrawer.addText( &textDriversNew[index++] );
    mainDrawer.addText( &textDriversNew[index++] );

    index = 0;
    mainDrawer.addText( &cursorDriversNew[index++] );
    mainDrawer.addText( &cursorDriversNew[index++] );
    mainDrawer.addText( &cursorDriversNew[index++] );
    mainDrawer.addText( &cursorDriversNew[index++] );
    mainDrawer.addPrimitive( background );

    for ( auto& ptrToDrawer: cursorDriversNew )
        ptrToDrawer.isVisible = false;

    for ( auto& ptrToDrawer: textDriversNew )
        ptrToDrawer.getFontDrawerRef().setColor( defaultColor );

    textDriversNew[currentSelectedItem].getFontDrawerRef().setColor( colorSelected );
    cursorDriversNew[currentSelectedItem].isVisible = true;

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

            if ( ioEvent.type == SDL_MOUSEMOTION )
            {
                const auto x = ioEvent.button.x;
                const auto y = ioEvent.button.y;

                const auto lineId = horizontalFocus( y );

                if ( lineId >= 0 )
                {
                    for ( auto& ptrToDrawer: cursorDriversNew )
                        ptrToDrawer.isVisible = false;

                    for ( auto& ptrToDrawer: textDriversNew )
                        ptrToDrawer.getFontDrawerRef().setColor( defaultColor );

                    currentSelectedItem = lineId;
                    currentSelectedItem %= itemsCount;
                    textDriversNew[currentSelectedItem].getFontDrawerRef().setColor( colorSelected );
                    cursorDriversNew[currentSelectedItem].isVisible = true;
                }
            }

            if ( ioEvent.type == SDL_MOUSEBUTTONDOWN )
            {
                if ( ioEvent.button.button == SDL_BUTTON_LEFT )
                {
                    const auto x = ioEvent.button.x;
                    const auto y = ioEvent.button.y;

                    const auto lineId = horizontalFocus( y );

                    if ( lineId >= 0 )
                    {
                        currentSelectedItem = lineId;
                        currentSelectedItem %= itemsCount;
                        quitLocal = true;
                    }
                }
            }

            if ( ioEvent.type == SDL_KEYDOWN )
            {
                auto keyValue = ioEvent.key.keysym.sym;

                for ( auto& ptrToDrawer: cursorDriversNew )
                    ptrToDrawer.isVisible = false;

                for ( auto& ptrToDrawer: textDriversNew )
                    ptrToDrawer.getFontDrawerRef().setColor( defaultColor );

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

                textDriversNew[currentSelectedItem].getFontDrawerRef().setColor( colorSelected );
                cursorDriversNew[currentSelectedItem].isVisible = true;
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

void TMainMenu::addItem( const string& text )
{
    const auto id = textDriversNew.size();
    textDriversNew.push_back( TFontDrawer( renderer, fontFile, fontSize ) );
    textDriversNew[id].getFontDrawerRef().setText( text );
    textDriversNew[id].getFontDrawerRef().setPoint( { background.width / 2 - 50, horizontalBorders[index] }, TTextAlignment::leftAlignment );

    cursorDriversNew.push_back( TFontDrawer( renderer, fontFile, fontSize ) );
    cursorDriversNew[id].getFontDrawerRef().setText( ">" );
    cursorDriversNew[id].getFontDrawerRef().setPoint( { background.width / 2 - 70, horizontalBorders[index++] }, TTextAlignment::leftAlignment );
    cursorDriversNew[id].getFontDrawerRef().setColor( colorSelected );
    cursorDriversNew[id].isVisible = false;
}
