#ifndef _TFONTDRAWER_CPP_
#define _TFONTDRAWER_CPP_

#include "TFontTTF.h"

using namespace io_submodule;

class TFontDrawer
{
    public:
        TFontDrawer( TRenderer& renderer, const string pathToTtf, const size_t fontSize );
        ~TFontDrawer();

        TFontDrawer( TFontDrawer&& old ) noexcept;
        TFontDrawer& operator=( TFontDrawer&& oldVal ) noexcept;

        void setText( const string& textToPrint );
        void drawText();

        TFontTTF& getFontDrawerRef();

        bool isVisible = true;

    private:

        TFontTTF fontRenderer;
};


#endif
