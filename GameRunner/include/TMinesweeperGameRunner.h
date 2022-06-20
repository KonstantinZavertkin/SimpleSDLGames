#ifndef _TMINESWEEPERGAMERUNNER_H_
#define _TMINESWEEPERGAMERUNNER_H_

#include "TRenderer.h"
#include "IAbstractRunner.h"

using namespace io_submodule;

class TMinesweeperGameRunner : public IAbstractRunner
{
    public:
        TMinesweeperGameRunner( TRenderer& rendererRef );

        void init() override;
        void run() override;

    private:

        TCellsFieldParams cellsFieldParams;
};

#endif // _TMINESWEEPERGAMERUNNER_H_
