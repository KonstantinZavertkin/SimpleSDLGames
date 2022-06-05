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

    void TCellsChain::initCellsChain( TCoords startPosition, size_t snakeLength )
    {
        for ( size_t i = 0; i < snakeLength; ++i )
        {
            auto x = startPosition.first;
            auto y = startPosition.second + snakeLength - i - 1;
            TExtendedCell tempCell;
            tempCell.thisCoordinates = make_pair( x, y );
            tempCell.moveDirection = make_pair( 0, 1 );
            snakeCells.push_back( tempCell );
            gameField.field[x][y].currentState = TCellStates::snakeBodyStateKey;
        }
    };

    void TCellsChain::turn( TCoords rotateVector )
    {
        TExtendedCell& headCell = snakeCells.front();

        auto [x, y] = headCell.moveDirection;
        auto [dx, dy] = rotateVector;

        if ( ( x + dx != 0 ) || ( y + dy != 0 ) )
            snakeCells.front().moveDirection = rotateVector;
    };

    void TCellsChain::step()
    {
        bool isFoodFound = false;

        auto snakeCellsCopy = snakeCells;
        
        // Handle body
        size_t cellsSize = snakeCellsCopy.size();

        for ( size_t i = 0; i < cellsSize; ++i )
        {
            auto& [x, y] = snakeCellsCopy[i].thisCoordinates;
            auto [dx, dy] = snakeCellsCopy[i].moveDirection;

            x += dx;
            y += dy;

            if ( i == 0 )
                if ( x < 0 || x >= gameField.fieldSize.first || y < 0 || y >= gameField.fieldSize.second )
                {
                    gameOverFlag = true;
                    break;
                }

            auto state = gameField.field[x][y].currentState;
            
            if ( i == 0 )
                if ( state == TCellStates::snakeBodyStateKey || state == TCellStates::snakeTailStateKey )
                {
                    gameOverFlag = true;
                    break;
                }

            if ( state == TCellStates::eatStateKey )
                isFoodFound = true;
        }

        if ( isFoodFound )
        {
            TExtendedCell lastCellBuffer = snakeCells.back();
            snakeCellsCopy.push_back( lastCellBuffer );
        }

        //! Copy moveDirection along chain
        cellsSize = snakeCellsCopy.size();

        for ( int i = cellsSize - 1; i > 0; --i )
            snakeCellsCopy[i].moveDirection = snakeCellsCopy[i - 1].moveDirection;

        for ( auto& cell : snakeCells )
        {
            auto [x, y] = cell.thisCoordinates;
            gameField.field[x][y].currentState = TCellStates::backgroundStateKey;
        }

        if ( !gameOverFlag )
            snakeCells = snakeCellsCopy;

        for ( auto& cell : snakeCells )
        {
            auto [x, y] = cell.thisCoordinates;
            gameField.field[x][y].currentState = TCellStates::snakeBodyStateKey;
        }

        auto [x, y] = snakeCells.front().thisCoordinates;
        gameField.field[x][y].currentState = TCellStates::snakeHeadStateKey;
    };

    bool TCellsChain::isGameOver()
    {
        return gameOverFlag;
    };

} 
