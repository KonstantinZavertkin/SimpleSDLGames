#ifndef _TMAINMENU_H_
#define _TMAINMENU_H_

#include "TRenderer.h"
#include "TDrawer.h"

class TMainMenu
{
    public:
        TMainMenu( TRenderer& rendererRef );

        void show();

        TRectangleDescription background;

        vector<TFontDrawer*> textPrinters;

        size_t currentSelectedItem = 0;
        size_t itemsCount = 3;

        TColorRGB colorSelected = { 0xFF, 0x00, 0xFF, 0xFF };
        SDL_Color defaultColor = { 0, 0xFF, 0xFF, 0xFF };

        string fontFile;
        size_t fontSize = 0;

        TRenderer& renderer;
};

#endif
