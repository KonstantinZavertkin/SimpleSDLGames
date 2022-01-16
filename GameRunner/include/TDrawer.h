#ifndef _TDRAWER_H_
#define _TDRAWER_H_

#include <vector>

#include "CommonTypes.hpp"
#include "TFieldDrawer.h"
#include "TFontDrawer.h"
#include "TRenderer.h"

namespace io_submodule
{
    class TDrawer
    {
        public:
            TDrawer( TRenderer& rendererRef );
            ~TDrawer();

            std::vector<TRectangleDescription> staticPrimitives;

            TFieldDrawer* mainFieldDrawer = nullptr;
            TFieldDrawer* nextFigureFieldDrawer = nullptr;
            TFontDrawer* scorePrinter = nullptr;

            void drawSequentially();

        private:
            TRenderer& renderer;
    };
};

#endif
