#ifndef _TFONTTTF_H_
#define _TFONTTTF_H_

#include "TSurface.h"
#include "TTexture.h"
#include "TDrawer.h"

namespace io_submodule
{
    using namespace std;

    class TFontTTF
    {
        public:
            
            TFontTTF( TDrawer& renderer, const string pathToTtf, const size_t fontSize );
            ~TFontTTF();

            void setPoint( pair<size_t, size_t> point );
            pair<size_t, size_t> getPoint() const;

            void setText( const string& strToPrint );
            TSurface& getTextSurface();
            TTexture& getTextTexture();

        private:

            pair<size_t, size_t> point;

            TTF_Font* font = nullptr;
            TSurface surface;

            string strToPrint;

            TDrawer& drawer;
            TTexture texture;
    };

    
}

#endif