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

        virtual ~TFieldDrawer();

        //! Draw main game field
        virtual void drawField() = 0;

        TRenderer& renderer;

    protected:
        TGameField& gameField;
        
        TCellRectangles& cellRectangles;
};

class TPrimitivesFieldDrawer : public TFieldDrawer
{
    public:
        TPrimitivesFieldDrawer( TGameField& gameField, TRenderer& drawer, TCellRectangles& cellRectangles );

        void drawField() override;

        ~TPrimitivesFieldDrawer() override;

        function<pair<TColorRGB, bool>( const TCell& cell )> cellsMapper;
};

class TTexturesFieldDrawer : public TFieldDrawer
{
    public:
        TTexturesFieldDrawer( TGameField& gameField, TRenderer& drawer, TCellRectangles& cellRectangles );

        void drawField() override;

        ~TTexturesFieldDrawer() override;

        function<int( const TCell& cell )> cellsMapper;
        vector<TTexture>* textures = nullptr;

        string pathToBmp;
        TCoords textureSliceSize = { 0, 0 };
        size_t scalingFactor = 1;
};

#endif
