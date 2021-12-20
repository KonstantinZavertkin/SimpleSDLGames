#ifndef _TFIELDDRAWER_H
#define _TFIELDDRAWER_H

#include "TGameField.h"
#include "TDrawer.h"
#include "TCellRectangles.h"

using namespace std;
using namespace game_backend;
using namespace io_submodule;

pair<TColorRGB, bool> tetrisCellsMapper( const TCell& cell );
pair<TColorRGB, bool> snakeCellsMapper( const TCell& cell );

class TFieldDrawer
{
    public:
        TFieldDrawer( TGameField& gameField, TDrawer& drawer, TCellRectangles& cellRectangles ) : 
            gameField( gameField ), drawer( drawer ), cellRectangles( cellRectangles )
        {};

        ~TFieldDrawer(){};

        //! Draw main game field 
        void draw();

        void addStaticPrimitive( TRectangleDescription );

    private:
        TGameField& gameField;
        TDrawer& drawer;
        TCellRectangles& cellRectangles;

        vector<TRectangleDescription> staticPrimitives;
};

#endif
