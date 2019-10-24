#ifndef _TFIELDDRAWER_H
#define _TFIELDDRAWER_H

#include "TGameField.h"
#include "TSnake.h"
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

        TGameField& gameField;
        TDrawer& drawer;
        TCellRectangles& cellRectangles;

        void draw()
        {
            auto field = gameField.field;

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

                    drawer.draw( cr );

                    if ( field[i][j].currentState != TCellStates::backgroundStateKey )
                    {
                        cr.isFilled = false;
                        cr.color = { 0xFF, 0xFF, 0xFF, 0xFF };
                        drawer.draw( cr );
                    }
                }
            }

            drawer.updateScreen();
        }
};

#endif
