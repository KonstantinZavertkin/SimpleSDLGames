#ifndef _TFONTDRAWER_CPP_
#define _TFONTDRAWER_CPP_

#include "TFontTTF.h"

using namespace io_submodule;

class TFontDrawer
{
    public:
        TFontDrawer( TRenderer& renderer, const string pathToTtf, const size_t fontSize );
        ~TFontDrawer();

        void setText( const string& textToPrint );
        void drawText();

        TFontTTF& getFontDrawerRef();

    private:

        TFontTTF fontRenderer;
};


#endif
