#include "TMainMenu.h"

TMainMenu::TMainMenu( TRenderer& rendererRef )
    : renderer( rendererRef ), mainDrawer( rendererRef )
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

    mainDrawer.addPrimitive( background );

    for ( auto& ptrToDrawer: textDrawers )
        ptrToDrawer.isVisible = true;

    for ( auto& drawerRef : focusedTextDrawers )
       drawerRef.isVisible = false;

    for ( auto& ptrToDrawer: cursorDrawers )
        ptrToDrawer.isVisible = false;

    currentSelectedItem %= itemsCount;
    textDrawers[currentSelectedItem].isVisible = false;
    focusedTextDrawers[currentSelectedItem].isVisible = true;
    cursorDrawers[currentSelectedItem].isVisible = true;

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
                    for ( auto& ptrToDrawer: textDrawers )
                        ptrToDrawer.isVisible = true;

                    for ( auto& drawerRef : focusedTextDrawers )
                       drawerRef.isVisible = false;

                    for ( auto& ptrToDrawer: cursorDrawers )
                        ptrToDrawer.isVisible = false;

                    currentSelectedItem = lineId;
                    currentSelectedItem %= itemsCount;
                    textDrawers[currentSelectedItem].isVisible = false;
                    focusedTextDrawers[currentSelectedItem].isVisible = true;
                    cursorDrawers[currentSelectedItem].isVisible = true;
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

                for ( auto& ptrToDrawer: textDrawers )
                    ptrToDrawer.isVisible = true;

                for ( auto& drawerRef : focusedTextDrawers )
                   drawerRef.isVisible = false;

                for ( auto& ptrToDrawer: cursorDrawers )
                    ptrToDrawer.isVisible = false;

                currentSelectedItem %= itemsCount;
                textDrawers[currentSelectedItem].isVisible = false;
                focusedTextDrawers[currentSelectedItem].isVisible = true;
                cursorDrawers[currentSelectedItem].isVisible = true;
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

void TMainMenu::generateHorizontalBorders( size_t startY, size_t stopY, size_t count )
{
    horizontalBorders = vector<size_t>();
    const auto stepSize = ( stopY - startY ) / count;

    for ( size_t i = 0; i < count + 1; ++i )
       horizontalBorders.push_back( startY + i * stepSize );
}

void TMainMenu::addItem( const string& text )
{
    ++itemsCount;
    const auto id = textDrawers.size();
    textDrawers.emplace_back( renderer, fontFile, fontSize );
    textDrawers[id].getFontDrawerRef().setText( text );
    textDrawers[id].getFontDrawerRef().setPoint( { background.width / 2 - 50, horizontalBorders[index] }, TTextAlignment::leftAlignment );

    focusedTextDrawers.emplace_back( renderer, fontFile, fontSize );
    focusedTextDrawers[id].getFontDrawerRef().setText( text );
    focusedTextDrawers[id].getFontDrawerRef().setPoint( { background.width / 2 - 50, horizontalBorders[index] }, TTextAlignment::leftAlignment );
    focusedTextDrawers[id].getFontDrawerRef().setColor( colorSelected );
    focusedTextDrawers[id].isVisible = false;

    cursorDrawers.emplace_back( renderer, fontFile, fontSize );
    cursorDrawers[id].getFontDrawerRef().setText( ">" );
    cursorDrawers[id].getFontDrawerRef().setPoint( { background.width / 2 - 70, horizontalBorders[index++] }, TTextAlignment::leftAlignment );
    cursorDrawers[id].getFontDrawerRef().setColor( colorSelected );
    cursorDrawers[id].isVisible = false;
}

void TMainMenu::setUpDrawer()
{
    for ( auto& ref : textDrawers )
        mainDrawer.addText( &ref );

    for ( auto& ref : focusedTextDrawers )
        mainDrawer.addText( &ref );

    for ( auto& ref : cursorDrawers )
        mainDrawer.addText( &ref );
}
