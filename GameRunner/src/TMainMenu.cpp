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

    for ( auto& ptrToDrawer: extendedCursorDrawers )
        ptrToDrawer.isVisible = false;

    currentSelectedItem %= itemsCount;
    textDrawers[currentSelectedItem].isVisible = false;
    focusedTextDrawers[currentSelectedItem].isVisible = true;
    cursorDrawers[currentSelectedItem].isVisible = true;

    if ( extendedCursor )
        extendedCursorDrawers[currentSelectedItem].isVisible = true;

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

                    for ( auto& ptrToDrawer: extendedCursorDrawers )
                        ptrToDrawer.isVisible = false;

                    currentSelectedItem = lineId;
                    currentSelectedItem %= itemsCount;
                    textDrawers[currentSelectedItem].isVisible = false;
                    focusedTextDrawers[currentSelectedItem].isVisible = true;
                    cursorDrawers[currentSelectedItem].isVisible = true;

                    if ( extendedCursor )
                        extendedCursorDrawers[currentSelectedItem].isVisible = true;
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

                for ( auto& ptrToDrawer: extendedCursorDrawers )
                    ptrToDrawer.isVisible = false;

                currentSelectedItem %= itemsCount;
                textDrawers[currentSelectedItem].isVisible = false;
                focusedTextDrawers[currentSelectedItem].isVisible = true;
                cursorDrawers[currentSelectedItem].isVisible = true;

                if ( extendedCursor )
                    extendedCursorDrawers[currentSelectedItem].isVisible = true;
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

void TMainMenu::initGridParams( size_t startY, size_t height )
{
    itemsGridStartY = startY;
    itemsLineHeight = height;
}

void TMainMenu::addLabelUnderItems( const string& text )
{
    TFontDrawer label( renderer, fontFile, fontSize );
    label.setText( text );
    label.setColor( labelsColor );
    label.setPoint( { background.width / 2 - 50, itemsGridStartY - itemsLineHeight - 10 }, TTextAlignment::leftAlignment );

    labelsDrawers.push_back( std::move( label ) );
}

void TMainMenu::addLabel( TFontDrawer&& fontDrawer )
{
    fontDrawer.setColor( labelsColor );
    labelsDrawers.push_back( std::move( fontDrawer ) );
}

void TMainMenu::addItem( const string& text )
{
    const auto gridVal = itemsGridStartY + itemsCount * itemsLineHeight;
    horizontalBorders.push_back( gridVal );
    const auto id = textDrawers.size();

    textDrawers.emplace_back( renderer, fontFile, fontSize );
    textDrawers[id].setText( text );
    textDrawers[id].setPoint( { background.width / 2 - itemsBias, gridVal }, TTextAlignment::leftAlignment );

    focusedTextDrawers.emplace_back( renderer, fontFile, fontSize );
    focusedTextDrawers[id].setText( text );
    focusedTextDrawers[id].setPoint( { background.width / 2 - itemsBias, gridVal }, TTextAlignment::leftAlignment );
    focusedTextDrawers[id].setColor( colorSelected );
    focusedTextDrawers[id].isVisible = false;

    cursorDrawers.emplace_back( renderer, fontFile, fontSize );
    cursorDrawers[id].setText( ">" );
    cursorDrawers[id].setPoint( { background.width / 2 - cursorBias, gridVal }, TTextAlignment::leftAlignment );
    cursorDrawers[id].setColor( colorSelected );
    cursorDrawers[id].isVisible = false;

    if ( extendedCursor )
    {
        extendedCursorDrawers.emplace_back( renderer, fontFile, fontSize );
        extendedCursorDrawers[id].setText( extendedCursorLabel );
        extendedCursorDrawers[id].setPoint( { background.width / 2 - cursorBias, gridVal }, TTextAlignment::rightAlignment );
        extendedCursorDrawers[id].setColor( labelsColor );
        extendedCursorDrawers[id].isVisible = false;
    }

    ++itemsCount;
}

void TMainMenu::setUp()
{
    const auto gridVal = itemsGridStartY + itemsCount * itemsLineHeight;
    horizontalBorders.push_back( gridVal );

    for ( auto& ref : labelsDrawers )
       mainDrawer.addText( &ref );

    for ( auto& ref : textDrawers )
        mainDrawer.addText( &ref );

    for ( auto& ref : focusedTextDrawers )
        mainDrawer.addText( &ref );

    for ( auto& ref : cursorDrawers )
        mainDrawer.addText( &ref );

    for ( auto& ref : extendedCursorDrawers )
        mainDrawer.addText( &ref );
}

void TMainMenu::addExtendedCursor( const string& str )
{
    extendedCursor = true;
    extendedCursorLabel = str;
}
