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

            TFontTTF( TFontTTF&& oldObj );
            TFontTTF& operator=( TFontTTF&& oldObj );

            void setPoint( TCoords point, TTextAlignment alignment );
            void setAlignment( TTextAlignment alignment );
            void setColor( TColorRGB rgba );
            TCoords getPoint() const;
            void setText( const string& strToPrint );

            void drawText();

            TSurface& getTextSurface();
            TTexture& getTextTexture();

        private:

            TTF_Font* font = nullptr;
            TCoords point;
            TCoords alignmentPoint;
            string strToPrint;
            SDL_Color color = { 0, 255, 255, 255 };
            SDL_Color colorPrev = { 0, 255, 255, 255 };
            bool flagToUpdateTexture = false;
            TTextAlignment currentAlignment = TTextAlignment::leftAlignment;

            TSurface surface;
            TRenderer& renderer;
            TTexture texture;
    };

    
}

#endif