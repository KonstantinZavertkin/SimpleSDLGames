#ifndef _TFONTDRAWER_H_
#define _TFONTDRAWER_H_

#include "TFontTTF.h"

using namespace io_submodule;

class TFontDrawer
{
    public:
        TFontDrawer( TRenderer& renderer, const string pathToTtf, const size_t fontSize );
        ~TFontDrawer();
        void setPoint( TCoords point, TTextAlignment alignment );
        void setColor( const TColorRGB& colorRgb );

        TFontDrawer( TFontDrawer&& old ) noexcept;
        TFontDrawer& operator=( TFontDrawer&& oldVal ) noexcept;

        void setText( const string& textToPrint );
        void drawText();

        bool isVisible = true;

    private:

        TFontTTF& getFontDrawerRef();

        TFontTTF fontRenderer;
};


#endif // _TFONTDRAWER_H_
