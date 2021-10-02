#ifndef _TRENDERER_H_
#define _TRENDERER_H_

#include <iostream>
#include "sdl2_include.h"
#include "TWindow.h"
//#include "TTexture.h"
//#include "TSurface.h"

namespace io_submodule
{
    class TRenderer
    {
        public:
            TRenderer( TWindow& window );
            ~TRenderer();

            SDL_Renderer* getRenderer();

        private:
            SDL_Renderer* renderer = nullptr;

            TRenderer( const TRenderer& ) = delete;
            TRenderer& operator=( const TRenderer& ) = delete;
    };
};

#endif // _TRENDERER_H_