#include "TFontTTF.h"

namespace io_submodule
{
    TFontTTF::TFontTTF( TRenderer& rendererRef, const string pathToTtf, const size_t fontSize )
        : drawer( rendererRef ), texture( rendererRef )
    {
        point = {};

        int ttfInitCode = TTF_Init();

        if ( ttfInitCode != 0 )
        {
            const string errorMsg = string( "TTF_OpenFont: " + string( TTF_GetError() ) );
            throw std::runtime_error( errorMsg );
        }

        font = TTF_OpenFont( pathToTtf.c_str(), fontSize );

        if ( font == nullptr )
        {
            const string errorMsg = string( "TTF_OpenFont: " + string( TTF_GetError() ) );
            throw std::runtime_error( errorMsg );
        }
    }

    TFontTTF::~TFontTTF()
    {
        if ( font )
        {
            TTF_CloseFont( font );
            font = nullptr;
        }

        TTF_Quit();
    }

    void TFontTTF::setPoint( TCoords point )
    {
        this->point = point;
    }

    TCoords TFontTTF::getPoint() const
    {
        return point;
    }

    void TFontTTF::setText( const string& strToPrintVar )
    {
        if ( this->strToPrint != strToPrintVar )
        {
            this->strToPrint = strToPrintVar;

            SDL_Color color = { 0, 255, 255, 255 };

            surface = TSurface( TTF_RenderText_Blended( font, this->strToPrint.c_str(), color ) );
            texture.updateSurface( surface );
        }

        drawer.draw( texture, point );
    }

    TSurface& TFontTTF::getTextSurface()
    {
        return surface;
    }

    TTexture& TFontTTF::getTextTexture()
    {
        return texture;
    }
}
