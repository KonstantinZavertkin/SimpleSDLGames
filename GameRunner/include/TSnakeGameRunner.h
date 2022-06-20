#ifndef _TSNAKERUNNER_H_
#define _TSNAKERUNNER_H_

#include "TSnakeGame.h"
#include "IAbstractRunner.h"

class TSnakeGameRunner : public IAbstractRunner
{
    public:
        TSnakeGameRunner( TRenderer& renderer );

        void init() override;
        void run() override;

        TCellsFieldParams cellsFieldParams;
        TRectangleDescription gameFieldBound;
};

#endif
