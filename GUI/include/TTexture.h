#ifndef _TTEXTURE_H_
#define _TTEXTURE_H_

#include "sdl2_include.h"
#include "TSurface.h"

namespace io_submodule
{
    class TRenderer;

    class TTexture
    {
        public:

            TTexture( TRenderer& renderer );
            TTexture( TRenderer& renderer, TSurface& surface );
            ~TTexture();

            void updateSurface( TSurface& );

            TSurface& getSurface();
            SDL_Texture* getTexturePtr();

        private:
            SDL_Texture* texturePtr = nullptr;
            TRenderer& renderer;
            TSurface surface;

            TTexture( const TTexture& ) = delete;
            TTexture& operator=( const TTexture& ) = delete;
    };
}

#endif // _TTEXTURE_H_#endif // _TWINDOW_H_
