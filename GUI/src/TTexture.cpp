#include "TTexture.h"

namespace io_submodule
{
    TTexture::TTexture( TRenderer& renderer, TSurface& surface )
    {
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
    };

    SDL_Texture* TTexture::getTexturePtr()
    {
        return texturePtr;
    };
}; 
