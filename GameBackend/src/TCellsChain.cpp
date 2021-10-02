#include "TCellsChain.h"
#include <tuple>
#include <iostream>

namespace game_backend
{
    using namespace std;

    TCellsChain::TCellsChain( TGameField& gameField ) : gameField( gameField )
    {};

    TCellsChain::~TCellsChain()
    {};

    void TCellsChain::initCellsChain( pair<size_t, size_t> startPosition, size_t snakeLength )
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

    void TCellsChain::turn( pair<int, int> rotateVector )
    {
        auto headCellCoords = snakeCells.front();
        auto x = headCellCoords.first;
        auto y = headCellCoords.second;

        gameField.field[x][y].moveDirectionDelta = rotateVector;
    };

    void TCellsChain::step()
    {
        auto fieldSize = gameField.fieldSize;
        bool isFoodFound = false;
        TCell lastCellBuffer;
        
        // Handle body
        for ( size_t i = 0; i < snakeCells.size(); ++i )
        {
            auto x = snakeCells[i].first;
            auto y = snakeCells[i].second;
            auto moveVector = gameField.field[x][y].moveDirection;
            auto moveVectorDelta = gameField.field[x][y].moveDirectionDelta;

            if ( moveVectorDelta.first != 0 || moveVectorDelta.second != 0 )
            {
                auto condition0 = moveVector.first != moveVectorDelta.first * -1;
                auto condition1 = moveVector.second != moveVectorDelta.second * -1;

                if ( condition0 && condition1 )
                    moveVector = moveVectorDelta;
            }

            lastCellBuffer = gameField.field[x][y];
            gameField.field[x][y].currentState = TCellStates::backgroundStateKey;
            gameField.field[x][y].moveDirection = make_pair( 0, 0 );

            if ( ( x == 0 && moveVector.first < 0 ) || ( y == 0 && moveVector.second < 0 ) )
            {
                gameOverFlag = true;
                continue;
            }
            
            snakeCells[i].first += moveVector.first;
            snakeCells[i].second += moveVector.second;
            
            x = snakeCells[i].first;
            y = snakeCells[i].second;

            if ( x >= fieldSize.first || y >= fieldSize.second )
            {
                gameOverFlag = true;
                continue;
            }

            auto state = gameField.field[x][y].currentState;

            if ( state == TCellStates::snakeBodyStateKey || state == TCellStates::snakeTailStateKey )
            {
                gameOverFlag = true;
                continue;
            }

            if ( state == TCellStates::eatStateKey )
                isFoodFound = true;

            gameField.field[x][y].currentState = TCellStates::snakeBodyStateKey;
            gameField.field[x][y].moveDirection = moveVector;
        }

        if ( isFoodFound )
        {
            auto x = lastCellBuffer.thisCoordinates.first;
            auto y = lastCellBuffer.thisCoordinates.second;
            gameField.field[x][y] = lastCellBuffer;
            snakeCells.push_back( make_pair( x, y ) );
        }

        if ( !gameOverFlag )
            updateSnakeHeadAndTail();
    };

    bool TCellsChain::isGameOver()
    {
        return gameOverFlag;
    };

    void TCellsChain::updateSnakeHeadAndTail()
    {
        auto headCellCoords = snakeCells.front();
        auto xHead = headCellCoords.first;
        auto yHead = headCellCoords.second;
        gameField.field[xHead][yHead].currentState = TCellStates::snakeHeadStateKey;

        auto tailCellCoords = snakeCells.back();
        auto xTail = tailCellCoords.first;
        auto yTail = tailCellCoords.second;
        gameField.field[xTail][yTail].currentState = TCellStates::snakeTailStateKey;

        auto moveVector = gameField.field[xTail][yTail].moveDirection;
        auto moveVectorDelta = gameField.field[xTail][yTail].moveDirectionDelta;

        if ( moveVectorDelta.first != 0 || moveVectorDelta.second != 0 )
        {
            auto condition0 = moveVector.first != moveVectorDelta.first * -1;
            auto condition1 = moveVector.second != moveVectorDelta.second * -1;

            if ( condition0 && condition1 )
                gameField.field[xTail][yTail].moveDirection = moveVectorDelta;
        }

        gameField.field[xTail][yTail].moveDirectionDelta = { 0, 0 };
    };
} 
