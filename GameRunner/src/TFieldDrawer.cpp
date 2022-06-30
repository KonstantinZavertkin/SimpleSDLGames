#include "TFieldDrawer.h"

pair<TColorRGB, bool> tetrisCellsMapper( const TCell& cell )
{
    if ( cell.currentState == TCellStates::redColorStateKey )
        return { { 0xFF, 0x00, 0x00, 0xFF }, true };
    
    if ( cell.currentState == TCellStates::greenColorStateKey )
        return { { 0x00, 0xFF, 0x00, 0xFF }, true };
    
    if ( cell.currentState == TCellStates::blueColorStateKey )
        return { { 0x00, 0x00, 0xFF, 0xFF }, true };

    if ( cell.currentState == TCellStates::cyanColorStateKey )
        return { { 0x00, 0xFF, 0xFF, 0xFF }, true };
    
    if ( cell.currentState == TCellStates::magentaColorStateKey )
        return { { 0xFF, 0x00, 0xFF, 0xFF }, true };
    
    if ( cell.currentState == TCellStates::yellowColorStateKey )
        return { { 0xFF, 0xFF, 0x00, 0xFF }, true };

    if ( cell.currentState == TCellStates::orangeColorStateKey )
        return { { 0xFF, 0x7F, 0x50, 0xFF }, true };

    if ( cell.currentState == TCellStates::virtualFigure )
        return { { 0x80, 0x80, 0x80, 0xFF }, true };
    
    return { { 0x40, 0x40, 0x40, 0xFF }, false };
}

pair<TColorRGB, bool> snakeCellsMapper( const TCell& cell )
{
    if ( cell.currentState == TCellStates::backgroundStateKey )
        return { { 0x40, 0x40, 0x40, 0xFF }, false };

    if ( cell.currentState == TCellStates::snakeBodyStateKey )
        return { { 0xFF, 0x00, 0x00, 0xFF }, true };

    if ( cell.currentState == TCellStates::snakeHeadStateKey )
        return { { 0x00, 0x00, 0xFF, 0xFF }, true };

    if ( cell.currentState == TCellStates::snakeTailStateKey )
        return { { 0xFF, 0x00, 0x00, 0xFF }, true };

    if ( cell.currentState == TCellStates::eatStateKey )
        return { { 0x00, 0xFF, 0x00, 0xFF }, true };
    
    return { { 0x00, 0x00, 0x00, 0xFF }, false };
}

pair<TColorRGB, bool> tetrisCellsMapperDebug( const TCell& cell )
{
    if ( !cell.canBeMoved && 
         cell.currentState != TCellStates::backgroundStateKey &&
         cell.currentState != TCellStates::virtualFigure )
        return { { 0x80, 0x80, 0x80, 0xFF }, true };

    if ( cell.canBeMoved )
        return { { 0xFF, 0x00, 0x00, 0xFF }, true };

    return { { 0x00, 0x00, 0x00, 0xFF }, false };
}

TFieldDrawer::TFieldDrawer( TGameField& gameField, TRenderer& drawer, TCellRectangles& cellRectangles )
    : renderer( drawer ), gameField( gameField ), cellRectangles( cellRectangles )
{
}

TFieldDrawer::~TFieldDrawer()
{
}

TPrimitivesFieldDrawer::TPrimitivesFieldDrawer( TGameField& gameField, TRenderer& drawer, TCellRectangles& cellRectangles ) :
    TFieldDrawer( gameField, drawer, cellRectangles )
{
}

void TPrimitivesFieldDrawer::drawField()
{
    auto& field = gameField.field;

    for ( size_t i = 0; i < field.size(); ++i )
    {
        for ( size_t j = 0; j < field[i].size(); ++j )
        {
            auto cr = cellRectangles.getCellRectangle( i, j );
            cr.isFilled = true;

            auto [color, isHaveBorder] = cellsMapper( field[i][j] );
            cr.color = color;
            renderer.draw( cr );

            if ( isHaveBorder )
            {
                cr.isFilled = false;
                cr.color = { 0xFF, 0xFF, 0xFF, 0xFF };
                renderer.draw( cr );
            }
        }
    }
}

TPrimitivesFieldDrawer::~TPrimitivesFieldDrawer()
{
}

TTexturesFieldDrawer::TTexturesFieldDrawer( TGameField& gameField, TRenderer& drawer, TCellRectangles& cellRectangles ):
    TFieldDrawer( gameField, drawer, cellRectangles )
{
}

void TTexturesFieldDrawer::drawField()
{
    auto& field = gameField.field;

    for ( size_t i = 0; i < field.size(); ++i )
    {
        for ( size_t j = 0; j < field[i].size(); ++j )
        {
            auto cr = cellRectangles.getCellRectangle( i, j );

            const auto textureId = cellsMapper( field[i][j] );

            TCoords coords = { cr.xStart, cr.yStart };
            renderer.draw( ( *textures )[textureId], coords );
        }
    }
}

TTexturesFieldDrawer::~TTexturesFieldDrawer()
{
}
