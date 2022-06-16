#ifndef _TMINESWEEPERGAMERUNNER_H_
#define _TMINESWEEPERGAMERUNNER_H_

#include "TRenderer.h"

using namespace io_submodule;

class TMinesweeperGameRunner
{
    public:
        TMinesweeperGameRunner( TRenderer& rendererRef );

        void init();
        void run();

        TRectangleDescription background;

        TCellsFieldParams cellsFieldParams;
        TRectangleDescription activeGameField;

        std::string fontFile;
        size_t fontSize = 0;
        
        TRenderer& renderer;
};

#endif // _TMINESWEEPERGAMERUNNER_H_
