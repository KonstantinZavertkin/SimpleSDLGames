#include "TSnake.h"

namespace game_backend
{
    TSnake::TSnake( TGameField& gameField ) : gameField( gameField )
    {
    };

    TSnake::~TSnake()
    {};

    void TSnake::initSnake( pair<size_t, size_t> startPosition, size_t snakeLength )
    {
        for ( size_t i = 0; i < snakeLength; ++i )
        {
            auto x = startPosition.first;
            auto y = startPosition.second + snakeLength - i - 1;
            snakeCells.push_back( make_pair( x, y ) );
            gameField.field[x][y].currentState = TCellStates::snakeBodyStateKey;
        }

        auto headCellCoords = snakeCells.front();
        auto xHead = headCellCoords.first;
        auto yHead = headCellCoords.second;
        gameField.field[xHead][yHead].currentState = TCellStates::snakeHeadStateKey;

        auto tailCellCoords = snakeCells.back();
        auto xTail = tailCellCoords.first;
        auto yTail = tailCellCoords.second;
        gameField.field[xTail][yTail].currentState = TCellStates::snakeTailStateKey;
    };

    void TSnake::turn( pair<int, int> rotateVector )
    {

    };

    void TSnake::step()
    {

    };
} 
