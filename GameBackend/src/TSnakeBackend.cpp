#include "TSnakeBackend.h"

#include <algorithm>

game_backend::TSnakeBackend::TSnakeBackend( TCoords fieldSize, size_t snakeLength )
    : gameField( fieldSize.first, fieldSize.second ), snake( gameField ), bestScoreStorage( pathToBestScoreFile )
{
    this->fieldSize = fieldSize;
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

bool game_backend::TSnakeBackend::stepGame()
{
    if ( ( clockCounter % 4 ) == 0 )
        performStep = true;

    if ( performStep )
    {
        if ( !rotationsQueue.empty() )
        {
            turn( rotationsQueue.front() );
            rotationsQueue.pop_front();
        }

        if ( !pauseGame )
            gameOver = step();

        performStep = false;
    }

    const auto stepsCount = static_cast<int>( snake.snakeCells.size() - initSnakeLength );
    timeDelay = max( 10, 50 - stepsCount );
    ++clockCounter;

    if ( gameOver )
       quitEvent = true;

    return gameOver;
}

void game_backend::TSnakeBackend::reset()
{
    gameOver = false;
    quitEvent = false;
    gameField = TGameField( fieldSize.first, fieldSize.second );
    snake.gameField = gameField;
    snake.initCellsChain( {1, 1}, initSnakeLength );
}
