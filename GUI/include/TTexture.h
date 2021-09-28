#ifndef _TTEXTURE_H_
#define _TTEXTURE_H_

#include <SDL2/SDL.h>
#include "TSurface.h"
#include "TRenderer.h"

namespace io_submodule
{
    class TTexture
    {
        public:
            TTexture( TRenderer& renderer, TSurface& surface );
            ~TTexture();

            SDL_Texture* getTexturePtr();

        private:
            SDL_Texture* texturePtr;

            TTexture( const TTexture& ) = delete;
            TTexture& operator=( const TTexture& ) = delete;
    };
}

#endif // _TTEXTURE_H_#endif // _TWINDOW_H_
