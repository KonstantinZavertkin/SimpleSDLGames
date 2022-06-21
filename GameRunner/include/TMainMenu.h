#ifndef _TMAINMENU_H_
#define _TMAINMENU_H_

#include "TRenderer.h"
#include "TDrawer.h"

class TMainMenu
{
    public:
        TMainMenu( TRenderer& rendererRef );

        size_t show();
        bool exitEvent() const;

        void addItem( const string& text );


        TRectangleDescription background;

        vector<TFontDrawer> textDriversNew;
        vector<TFontDrawer> cursorDriversNew;

        size_t currentSelectedItem = 0;
        size_t itemsCount = 4;

        TColorRGB colorSelected = { 0xFF, 0x00, 0xFF, 0xFF };
        TColorRGB defaultColor = { 0, 0xFF, 0xFF, 0xFF };

        string fontFile;
        size_t fontSize = 0;

        TRenderer& renderer;

        bool exitFlag = false;

        size_t index = 0;
        vector<size_t> horizontalBorders = { 200, 225, 250, 275, 300 };
};

#endif
