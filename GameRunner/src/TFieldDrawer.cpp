#include "TFieldDrawer.h"

void TFieldDrawer::draw()
{
    auto& field = gameField.field;

    for ( size_t i = 0; i < field.size(); ++i )
    {
        for ( size_t j = 0; j < field[i].size(); ++j )
        {
            auto cr = cellRectangles.getCellRectangle( i, j );
            cr.isFilled = true;

            if ( field[i][j].currentState == TCellStates::backgroundStateKey )
                cr.color = { 0x00, 0x00, 0x00, 0xFF };

            if ( field[i][j].currentState == TCellStates::snakeBodyStateKey )
                cr.color = { 0xFF, 0x00, 0x00, 0xFF };

            if ( field[i][j].currentState == TCellStates::snakeHeadStateKey )
                cr.color = { 0x00, 0x00, 0xFF, 0xFF };

            if ( field[i][j].currentState == TCellStates::snakeTailStateKey )
                cr.color = { 0xFF, 0x00, 0x00, 0xFF };

            if ( field[i][j].currentState == TCellStates::eatStateKey )
                cr.color = { 0x00, 0xFF, 0x00, 0xFF };
            

            if ( field[i][j].currentState == TCellStates::redColorStateKey )
                cr.color = { 0xFF, 0x00, 0x00, 0xFF };
            
            if ( field[i][j].currentState == TCellStates::greenColorStateKey )
                cr.color = { 0x00, 0xFF, 0x00, 0xFF };
            
            if ( field[i][j].currentState == TCellStates::blueColorStateKey )
                cr.color = { 0x00, 0x00, 0xFF, 0xFF };

            if ( field[i][j].currentState == TCellStates::cyanColorStateKey )
                cr.color = { 0x00, 0xFF, 0xFF, 0xFF };
            
            if ( field[i][j].currentState == TCellStates::magentaColorStateKey )
                cr.color = { 0xFF, 0x00, 0xFF, 0xFF };
            
            if ( field[i][j].currentState == TCellStates::yellowColorStateKey )
                cr.color = { 0xFF, 0xFF, 0x00, 0xFF };

            if ( field[i][j].currentState == TCellStates::orangeColorStateKey )
                cr.color = { 0xFF, 0x7F, 0x50, 0xFF };

            if ( field[i][j].currentState == TCellStates::virtualFigure )
                cr.color = { 0x80, 0x80, 0x80, 0xFF };

            drawer.draw( cr );

            if ( field[i][j].currentState != TCellStates::backgroundStateKey )
            {
                cr.isFilled = false;
                cr.color = { 0xFF, 0xFF, 0xFF, 0xFF };
                drawer.draw( cr );
            }
        }
    }

    for ( const auto& val : staticPrimitives )
        drawer.draw( val );
    
    drawer.updateScreen();
};

void TFieldDrawer::addStaticPrimitive( TRectangleDescription figureDescription )
{
    staticPrimitives.push_back( figureDescription );
};
