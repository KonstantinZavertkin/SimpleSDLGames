#ifndef _TFIELDDRAWER_H
#define _TFIELDDRAWER_H

#include <functional>
#include "TGameField.h"
#include "TRenderer.h"
#include "TCellRectangles.h"

using namespace std;
using namespace game_backend;
using namespace io_submodule;

pair<TColorRGB, bool> tetrisCellsMapper( const TCell& cell );
pair<TColorRGB, bool> snakeCellsMapper( const TCell& cell );
pair<TColorRGB, bool> tetrisCellsMapperDebug( const TCell& cell );

class TFieldDrawer
{
    public:
        TFieldDrawer( TGameField& gameField, TRenderer& drawer, TCellRectangles& cellRectangles );

        ~TFieldDrawer();

        //! Draw main game field 
        void draw();

        void addStaticPrimitive( TRectangleDescription );

        function<pair<TColorRGB, bool>( const TCell& cell )> cellsMapper;

        TRenderer& drawer;

    private:
        TGameField& gameField;
        
        TCellRectangles& cellRectangles;

        vector<TRectangleDescription> staticPrimitives;
};

#endif
