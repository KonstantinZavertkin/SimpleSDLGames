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

    void TFontTTF::setPoint( TCoords pointArg, TTextAlignment alignment )
    {
        this->point = pointArg;
        this->alignmentPoint = pointArg;
        
        setAlignment( alignment );
    }

    void TFontTTF::setAlignment( TTextAlignment alignment )
    {
        auto [x, y] = point;

        if ( alignment == TTextAlignment::centerAlignment )
            x -= texture.getSurface().getSurfaceWidth() / 2;

        if ( alignment == TTextAlignment::rightAlignment )
            x -= texture.getSurface().getSurfaceWidth();

        currentAlignment = alignment;
        alignmentPoint = { x, y };
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
            setAlignment( currentAlignment );
        }
    }

    void TFontTTF::drawText()
    {
        setText( strToPrint );
        renderer.draw( texture, alignmentPoint );
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
