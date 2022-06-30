#ifndef _TTETRISGAMERUNNER_H_
#define _TTETRISGAMERUNNER_H_

#include "TTetrisGame.h"
#include "IAbstractRunner.h"

class TTetrisGameRunner : public IAbstractRunner
{
    public:

        TTetrisGameRunner( TRenderer& renderer );

        void init() override;
        void run() override;

        TCellsFieldParams cellsFieldParams;
        TRectangleDescription gameFieldBound;
        TCellsFieldParams cellsInfoFieldParams;
        TRectangleDescription gameInfoField;
        TRectangleDescription infoFieldBound;
};

#endif
