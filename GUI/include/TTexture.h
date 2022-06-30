#ifndef _TTEXTURE_H_
#define _TTEXTURE_H_

#include <memory>
#include "sdl2_include.h"
#include "CommonTypes.hpp"
#include "TSurface.h"

namespace io_submodule
{
    class TRenderer;

    class TTexture
    {
        public:

            TTexture( TRenderer& renderer );
            TTexture( TRenderer& renderer, TSurface& surface );

            TTexture( TTexture&& oldVar ) noexcept;
            TTexture& operator=( TTexture&& oldVar ) noexcept;
            TTexture( const TTexture& ) = delete;
            TTexture& operator=( const TTexture& ) = delete;

            ~TTexture();

            void updateSurface( TSurface& surface );
            void setTexturePart( TCoords xy, TCoords hw );
            SDL_Rect* getPart();

            void setStartPoint( TCoords startXy );
            TCoords& getStartPoint();

            void setScalingFactor( size_t factor );
            size_t getScalingFactor();

            TSurface& getSurface();
            SDL_Texture* getTexturePtr();

        private:
            
            TRenderer& renderer;
            SDL_Texture* texturePtr = nullptr;
            std::unique_ptr<SDL_Rect> part = nullptr;
            
            TSurface surface;
            TCoords startPoint = { 0, 0 };
            size_t scalingFactor = 1;
    };
}

#endif // _TTEXTURE_H_#endif // _TWINDOW_H_
