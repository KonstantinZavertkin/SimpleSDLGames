#ifndef _TDRAWER_H_
#define _TDRAWER_H_

#include <SDL2/SDL.h>
#include "TTexture.h"
#include "TRenderer.h"
#include "TParams.h"

namespace io_submodule
{
    class TDrawer
    {
        public:
            TDrawer( TRenderer& renderer );
            ~TDrawer();

            void draw( TTexture& texture );
            void draw( TRectangleDescription rectangleParams );

            void updateScreen();

        private:
            TRenderer& rendererRef;
            
            TDrawer() = default;
            TDrawer( const TDrawer& ) = delete;
            TDrawer& operator=( const TDrawer& ) = delete;
    };
};

#endif
