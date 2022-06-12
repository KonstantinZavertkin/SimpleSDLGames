#ifndef _TFONTTTF_H_
#define _TFONTTTF_H_

#include "CommonTypes.hpp"
#include "TSurface.h"
#include "TTexture.h"
#include "TRenderer.h"

namespace io_submodule
{
    using namespace std;

    enum class TTextAlignment
    {
        leftAlignment, centerAlignment, rightAlignment
    };

    class TFontTTF
    {
        public:
            
            TFontTTF( TRenderer& renderer, const string pathToTtf, const size_t fontSize );
            ~TFontTTF();

            void setPoint( TCoords point, TTextAlignment alignment );
            void setColor( TColorRGB rgba );
            TCoords getPoint() const;
            void setText( const string& strToPrint );

            void drawText();

            TSurface& getTextSurface();
            TTexture& getTextTexture();

        private:

            TTF_Font* font = nullptr;
            TCoords point;
            string strToPrint;
            SDL_Color color = { 0, 255, 255, 255 };
            bool flagToUpdateTexture = false;

            TSurface surface;
            TRenderer& renderer;
            TTexture texture;
    };

    
}

#endif