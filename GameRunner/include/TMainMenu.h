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

        string fontFile;
        size_t fontSize = 0;

        TRenderer& renderer;
};

#endif
