#include "TSnakeGame.h"

namespace game_backend 
{

    TSnakeGame::TSnakeGame( pair<size_t, size_t> fieldSize, size_t snakeLength ) 
        : gameField( fieldSize.first, fieldSize.second ), snake( gameField )
    {
        snake.initCellsChain( { 1, 1 }, snakeLength );
    };

    TSnakeGame::~TSnakeGame()
    {
    };

    bool TSnakeGame::step()
    {
        snake.step();
        checkFood();
        return snake.isGameOver();
    };

    void TSnakeGame::turn( pair<int, int> rotateVector )
    {
        snake.turn( rotateVector );
    };

    void TSnakeGame::checkFood()
    {
        // Is required?
        bool isRequiredFood = true;

        for ( auto line : gameField.field )
        {
            for ( auto cell : line )
                if ( cell.currentState == TCellStates::eatStateKey )
                    isRequiredFood = false;
        }

        if ( isRequiredFood )
        {
            auto x = rand() % gameField.field.size();
            auto y = rand() % gameField.field[0].size();
            gameField.field[x][y].currentState = TCellStates::eatStateKey;
        }
    }

};