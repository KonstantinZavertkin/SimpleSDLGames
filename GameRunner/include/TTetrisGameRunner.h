#ifndef _TTETRISGAMERUNNER_H_
#define _TTETRISGAMERUNNER_H_

#include "TTetrisGame.h"

class TTetrisGameRunner
{
    public:

        TTetrisGameRunner( TRenderer& renderer );

        void init();
        void run();

        TRectangleDescription background;

        TCellsFieldParams cellsFieldParams;
        TRectangleDescription activeGameField;
        TRectangleDescription gameFieldBound;
        TCellsFieldParams cellsInfoFieldParams;
        TRectangleDescription gameInfoField;
        TRectangleDescription infoFieldBound;

        string fontFile;
        size_t fontSize = 0;
        
        TRenderer& renderer;
};

#endif
