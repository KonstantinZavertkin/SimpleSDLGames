#include "TSnakeBackend.h"

game_backend::TSnakeBackend::TSnakeBackend( TCoords fieldSize, size_t snakeLength )
    : gameField( fieldSize.first, fieldSize.second ), snake( gameField ), bestScoreStorage( pathToBestScoreFile )
{
    initSnakeLength = snakeLength;
    snake.initCellsChain({1, 1}, initSnakeLength);
}

bool game_backend::TSnakeBackend::step()
{
    snake.step();
    checkFood();
    return snake.isGameOver();
}

void game_backend::TSnakeBackend::turn(TCoords rotateVector)
{
    snake.turn( rotateVector );
}

void game_backend::TSnakeBackend::checkFood()
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
