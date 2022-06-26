#ifndef _TMAINMENU_H_
#define _TMAINMENU_H_

#include "TRenderer.h"
#include "TDrawer.h"

enum class TItemType
{
    autoPosition = 0,
    freePosition
};

class TMainMenu
{
    public:
        TMainMenu( TRenderer& rendererRef );

        size_t show();
        bool exitEvent() const;

        void generateHorizontalBorders( size_t startY, size_t stopY, size_t count );

        void addLabelUnderItems( const string& text );
        void addLabel( TFontDrawer&& fontDrawer );
        void addItem( const string& text );
        void setUpDrawer();

        TRectangleDescription background;

        vector<TFontDrawer> labelsDrawers;
        vector<TFontDrawer> textDrawers;
        vector<TFontDrawer> cursorDrawers;
        vector<TFontDrawer> focusedTextDrawers;

        TColorRGB colorSelected = { 0xFF, 0x00, 0xFF, 0xFF };
        TColorRGB defaultColor = { 0, 0xFF, 0xFF, 0xFF };

        string fontFile;
        size_t fontSize = 0;

        TRenderer& renderer;
        TDrawer mainDrawer;

        bool exitFlag = false;

        size_t index = 0;
        vector<size_t> horizontalBorders = {};

    private:
        size_t itemsGridStartY = 0;
        size_t itemsGridStartX = 0;
        size_t itemsLineHeight = 0;
        size_t itemsCount = 0;
        size_t currentSelectedItem = 0;
};

#endif
