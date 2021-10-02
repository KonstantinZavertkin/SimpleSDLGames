#include "TSnakeFunctions.h"
#include "TGameField.h"

namespace game_backend
{
    void checkFood( TGameField& field )
    {
        // Is required?
        bool isRequiredFood = true;

        for ( auto line : field.field )
        {
            for ( auto cell : line )
                if ( cell.currentState == TCellStates::eatStateKey )
                    isRequiredFood = false;
        }

        if ( isRequiredFood )
        {
            auto x = rand() % field.field.size();
            auto y = rand() % field.field[0].size();
            field.field[x][y].currentState = TCellStates::eatStateKey;
        }
    }
}