#ifndef _IABSTRACTRUNNER_H_
#define _IABSTRACTRUNNER_H_

#include "TRenderer.h"

using namespace io_submodule;

class IAbstractRunner
{
    public:
        IAbstractRunner( TRenderer& rendererRef );
        virtual ~IAbstractRunner();

        virtual void init() = 0;
        virtual void run() = 0;

        TRectangleDescription background;
        TRectangleDescription activeGameField;

        std::string fontFile;
        size_t fontSize = 0;

    protected:
        TRenderer& rendererRef;
};

#endif // _IABSTRACTRUNNER_H_
