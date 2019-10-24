#include "TSnake.h"
#include <tuple>

namespace game_backend
{
    TSnake::TSnake( TGameField& gameField ) : gameField( gameField )
    {};

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
            gameField.field[x][y].moveDirection = make_pair( 0, 1 );
        }

        updateSnakeHeadAndTail();
    };

    void TSnake::turn( pair<int, int> rotateVector )
    {
        auto headCellCoords = snakeCells.front();
        auto x = headCellCoords.first;
        auto y = headCellCoords.second;

        gameField.field[x][y].moveDirectionDelta = rotateVector;
    };

    void TSnake::step()
    {
        //auto fieldSize = gameField.fieldSize;

        for ( size_t i = 0; i < snakeCells.size(); ++i )
        {
            auto x = snakeCells[i].first;
            auto y = snakeCells[i].second;
            auto moveVector = gameField.field[x][y].moveDirection;
            auto moveVectorDelta = gameField.field[x][y].moveDirectionDelta;

            if ( moveVectorDelta.first || moveVectorDelta.second )
                moveVector = moveVectorDelta;

            gameField.field[x][y].currentState = TCellStates::backgroundStateKey;
            gameField.field[x][y].moveDirection = make_pair( 0, 0 );
            
            snakeCells[i].first += moveVector.first;
            snakeCells[i].second += moveVector.second;
            
            x = snakeCells[i].first;
            y = snakeCells[i].second;

            gameField.field[x][y].currentState = TCellStates::snakeBodyStateKey;
            gameField.field[x][y].moveDirection = moveVector;
        }

        updateSnakeHeadAndTail();
    };

    void TSnake::updateSnakeHeadAndTail()
    {
        auto headCellCoords = snakeCells.front();
        auto xHead = headCellCoords.first;
        auto yHead = headCellCoords.second;
        gameField.field[xHead][yHead].currentState = TCellStates::snakeHeadStateKey;

        auto tailCellCoords = snakeCells.back();
        auto xTail = tailCellCoords.first;
        auto yTail = tailCellCoords.second;
        gameField.field[xTail][yTail].currentState = TCellStates::snakeTailStateKey;
        //gameField.field[xTail][yTail].moveDirection = { 0, 0 };
        gameField.field[xTail][yTail].moveDirectionDelta = { 0, 0 };
    };
} 
