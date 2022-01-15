#ifndef _TDRAWER_H_
#define _TDRAWER_H_

#include "sdl2_include.h"
#include "TTexture.h"
#include "TRenderer.h"
#include "TParams.h"
#include "CommonTypes.hpp"

namespace io_submodule
{
    class TDrawer
    {
        public:
            TDrawer( TRenderer& renderer );
            ~TDrawer();

            void draw( TTexture& texture, TCoords point );
            void draw( TRectangleDescription rectangleParams );

            void resetScreen();
            void updateScreen();

            TRenderer& getRenderer();

        private:
            TRenderer& rendererRef;
            
            TDrawer() = delete;
            TDrawer( const TDrawer& ) = delete;
            TDrawer& operator=( const TDrawer& ) = delete;
    };
};

#endif
