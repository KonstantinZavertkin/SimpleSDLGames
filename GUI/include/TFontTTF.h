#ifndef _TFONTTTF_H_
#define _TFONTTTF_H_

#include "CommonTypes.hpp"
#include "TSurface.h"
#include "TTexture.h"
#include "TRenderer.h"

namespace io_submodule
{
    using namespace std;

    class TFontTTF
    {
        public:
            
            TFontTTF( TRenderer& renderer, const string pathToTtf, const size_t fontSize );
            ~TFontTTF();

            void setPoint( TCoords point );
            TCoords getPoint() const;

            void setText( const string& strToPrint );
            TSurface& getTextSurface();
            TTexture& getTextTexture();

        private:

            TCoords point;

            TTF_Font* font = nullptr;
            TSurface surface;

            string strToPrint;

            TRenderer& drawer;
            TTexture texture;
    };

    
}

#endif