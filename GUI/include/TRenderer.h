#ifndef _TRENDERER_H_
#define _TRENDERER_H_

#include <iostream>
#include "sdl2_include.h"
#include "CommonTypes.hpp"
#include "TWindow.h"
#include "TTexture.h"
#include "TSurface.h"

namespace io_submodule
{
    class TTexture;

    class TRenderer
    {
        public:
            TRenderer( TWindow& window );
            ~TRenderer();

            SDL_Renderer* getRenderer();

            void draw( TTexture& texture, TCoords point );
            void draw( TRectangleDescription rectangleParams );

            void resetScreen();
            void updateScreen();

        private:
            SDL_Renderer* renderer = nullptr;

            TRenderer( const TRenderer& ) = delete;
            TRenderer& operator=( const TRenderer& ) = delete;
    };
};

#endif // _TRENDERER_H_