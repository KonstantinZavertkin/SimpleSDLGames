#ifndef _TSNAKERUNNER_H_
#define _TSNAKERUNNER_H_

#include "TSnakeGame.h"

class TSnakeGameRunner
{
    public:
        TSnakeGameRunner( TRenderer& renderer );

        void init();
        void run();

        TRectangleDescription background;

        TCellsFieldParams cellsFieldParams;
        TRectangleDescription activeGameField;
        TRectangleDescription gameFieldBound;

        string fontFile;
        size_t fontSize = 0;

    private:

        TRenderer& renderer;
};

#endif
