#include "TFontTTF.h"

namespace io_submodule
{
    TFontTTF::TFontTTF( TRenderer& rendererRef, const string pathToTtf, const size_t fontSize )
        : renderer( rendererRef ), texture( rendererRef )
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

    void TFontTTF::setPoint( TCoords pointArg, TTextAlignment alignment  )
    {
        auto [x, y] = pointArg;

        if ( alignment == TTextAlignment::centerAlignment )
            x -= surface.getSurfaceWidth() / 2;

        if ( alignment == TTextAlignment::centerAlignment )
            x -= surface.getSurfaceWidth();

        this->point = { x, y };
    }

    void TFontTTF::setColor( TColorRGB rgba )
    {
        color.r = rgba.r;
        color.g = rgba.g;
        color.b = rgba.b;
        color.a = rgba.alpha;
        flagToUpdateTexture = true;
    }

    TCoords TFontTTF::getPoint() const
    {
        return point;
    }

    void TFontTTF::setText( const string& strToPrintVar )
    {
        if ( this->strToPrint != strToPrintVar || flagToUpdateTexture )
        {
            flagToUpdateTexture = false;
            this->strToPrint = strToPrintVar;

            surface = TSurface( TTF_RenderText_Blended( font, this->strToPrint.c_str(), color ) );
            texture.updateSurface( surface );
        }
    }

    void TFontTTF::drawText()
    {
        renderer.draw( texture, point );
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
