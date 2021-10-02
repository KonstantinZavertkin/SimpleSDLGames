#ifndef _TFIELDDRAWER_H
#define _TFIELDDRAWER_H

#include "TGameField.h"
#include "TDrawer.h"
#include "TCellRectangles.h"

using namespace std;
using namespace game_backend;
using namespace io_submodule;

class TFieldDrawer
{
    public:
        TFieldDrawer( TGameField& gameField, TDrawer& drawer, TCellRectangles& cellRectangles ) : 
            gameField( gameField ), drawer( drawer ), cellRectangles( cellRectangles )
        {};

        ~TFieldDrawer(){};
        void draw();

    private:
        TGameField& gameField;
        TDrawer& drawer;
        TCellRectangles& cellRectangles;
};

#endif
