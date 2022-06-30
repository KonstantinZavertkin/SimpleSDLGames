#ifndef _TMAINMENU_H_
#define _TMAINMENU_H_

#include "TRenderer.h"
#include "TDrawer.h"

//! Universal menu screen
//! Initialization:
//! Init "TRectangleDescription background;" at first
//! Call the initGridParams(...) method before calling addLabel(...), addLabelUnderItems(...), addItem(...), addExtendedCursor(...)
//! After this, call the setUp() method
//! Using:
//! Call show(). This returns selected items index
//! Check exit event by calling exitEvent()
class TMainMenu
{
    public:
        TMainMenu( TRenderer& rendererRef );

        void initGridParams( size_t startY, size_t height );

        void addLabel( TFontDrawer&& fontDrawer );
        void addLabelUnderItems( const string& text );
        void addItem( const string& text );
        void addExtendedCursor( const string& str );

        void setUp();

        size_t show();
        bool exitEvent() const;

        TRectangleDescription background;

        vector<TFontDrawer> labelsDrawers;
        vector<TFontDrawer> textDrawers;
        vector<TFontDrawer> focusedTextDrawers;
        vector<TFontDrawer> cursorDrawers;
        vector<TFontDrawer> extendedCursorDrawers;

        TColorRGB colorSelected = { 0xFF, 0x00, 0xFF, 0xFF };
        TColorRGB defaultColor = { 0, 0xFF, 0xFF, 0xFF };
        TColorRGB labelsColor = { 0xFF, 0xFF, 0x99, 0xFF };

        string fontFile;
        size_t fontSize = 0;

        TRenderer& renderer;
        TDrawer mainDrawer;

    private:

        bool exitFlag = false;
        bool extendedCursor = false;

        vector<size_t> horizontalBorders = {};
        string extendedCursorLabel;
        size_t itemsGridStartY = 0;
        size_t itemsGridStartX = 0;
        size_t itemsLineHeight = 0;
        size_t itemsCount = 0;
        size_t currentSelectedItem = 0;

        size_t cursorBias = 70;
        size_t itemsBias = 50;
};

#endif
