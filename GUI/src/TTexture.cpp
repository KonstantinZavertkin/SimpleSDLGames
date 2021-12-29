#include "TTexture.h"

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
    };

    TTexture::~TTexture()
    {
        if ( texturePtr != nullptr )
            SDL_DestroyTexture( texturePtr );
    }

    void TTexture::updateSurface( TSurface& surfaceRef )
    {
        surface = std::move( surfaceRef );
        texturePtr = SDL_CreateTextureFromSurface( renderer.getRenderer(), surface.getSurface() );
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
