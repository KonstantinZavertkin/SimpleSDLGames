#include "TFontTTF.h"
#include <memory>

namespace io_submodule
{
    TFontTTF::TFontTTF( TRenderer& rendererRef, const string pathToTtf, const size_t fontSize )
        : renderer( rendererRef ), texture( rendererRef )
    {
        point = {};

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
    }

    TFontTTF::TFontTTF( TFontTTF&& oldObj ) noexcept :
        surface( std::move( oldObj.surface ) ),
        renderer( oldObj.renderer ),
        texture( std::move( oldObj.texture ) )
    {
        font = oldObj.font;
        oldObj.font = nullptr;

        point = oldObj.point;
        alignmentPoint = oldObj.alignmentPoint;
        strToPrint = std::move( oldObj.strToPrint );
        color = oldObj.color;
        flagToUpdateTexture = oldObj.flagToUpdateTexture;
        currentAlignment = oldObj.currentAlignment;
    }

    TFontTTF& TFontTTF::operator=( TFontTTF&& oldObj ) noexcept
    {
        surface = std::move( oldObj.surface );
        texture = std::move( oldObj.texture );
        font = oldObj.font;
        oldObj.font = nullptr;

        point = oldObj.point;
        alignmentPoint = oldObj.alignmentPoint;
        strToPrint = std::move( oldObj.strToPrint );
        color = oldObj.color;
        flagToUpdateTexture = oldObj.flagToUpdateTexture;
        currentAlignment = oldObj.currentAlignment;
        return *this;
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

            SDL_Surface* surf = TTF_RenderText_Blended( font, this->strToPrint.c_str(), color );
            surface = TSurface( surf );
            texture.updateSurface( surface );
            setAlignment( currentAlignment );
        }
    }

    void TFontTTF::drawText()
    {
        if ( color.r != colorPrev.r ||
             color.g != colorPrev.g ||
             color.b != colorPrev.b ||
             color.a != colorPrev.a)
        {
            colorPrev = color;
            flagToUpdateTexture = true;
        }

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
