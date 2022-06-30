#include "TTexture.h"
#include "TRenderer.h"

namespace io_submodule
{
    TTexture::TTexture( TRenderer& rendererRef ) : renderer( rendererRef )
    {
    }

    TTexture::TTexture( TRenderer& rendererRef, TSurface& surfaceRef ) : renderer( rendererRef )
    {
        surface = std::move( surfaceRef );
        texturePtr = SDL_CreateTextureFromSurface( renderer.getRenderer(), surface.getSurface() );

        if ( texturePtr == nullptr )
        {
            std::string errorMsg = std::string( "SDL error: " ) + SDL_GetError();
            throw std::runtime_error( errorMsg );
        }
    }

    TTexture::TTexture( TTexture&& oldVar ) noexcept : renderer( oldVar.renderer )
    {
        texturePtr = oldVar.texturePtr;
        oldVar.texturePtr = nullptr;

        part = std::move( oldVar.part );
        surface = std::move( oldVar.surface );
        startPoint = oldVar.startPoint;
        scalingFactor = oldVar.scalingFactor;
    }

    TTexture& TTexture::operator=( TTexture&& oldVar ) noexcept
    {
        texturePtr = oldVar.texturePtr;
        oldVar.texturePtr = nullptr;

        part = std::move( oldVar.part );
        surface = std::move( oldVar.surface );
        startPoint = oldVar.startPoint;
        scalingFactor = oldVar.scalingFactor;

        return *this;
    };

    TTexture::~TTexture()
    {
        if ( texturePtr != nullptr )
        {
            SDL_DestroyTexture( texturePtr );
        }
    }

    void TTexture::updateSurface( TSurface& surfaceRef )
    {
        surface = std::move( surfaceRef );

        if ( texturePtr != nullptr )
        {
            SDL_DestroyTexture( texturePtr );
        }

        texturePtr = SDL_CreateTextureFromSurface( renderer.getRenderer(), surface.getSurface() );
    }

    void TTexture::setTexturePart( TCoords xy, TCoords hw )
    {
        part = std::make_unique<SDL_Rect>();
        part->x = xy.first;
        part->y = xy.second;
        part->h = hw.first;
        part->w = hw.second;
    }

    SDL_Rect* TTexture::getPart()
    {
        if ( part )
            return part.get();

        return nullptr;
    }

    void TTexture::setStartPoint( TCoords startXy )
    {
        startPoint = startXy;
    }

    TCoords& TTexture::getStartPoint()
    {
        return startPoint;
    }

    void TTexture::setScalingFactor( size_t factor )
    {
        scalingFactor = factor;
    }

    size_t TTexture::getScalingFactor()
    {
        return scalingFactor;
    }

    TSurface& TTexture::getSurface()
    {
        return surface;
    };

    SDL_Texture* TTexture::getTexturePtr()
    {
        return texturePtr;
    };
}; 
