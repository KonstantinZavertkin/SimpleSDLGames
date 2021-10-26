#include <iostream>
#include "TCellsBlock.h"

namespace game_backend
{
    TCellsBlock::TCellsBlock( TGameField& gameField ) : gameField( gameField )
    {};

    TCellsBlock::~TCellsBlock()
    {};

    void TCellsBlock::initFigure( pair<size_t, size_t> startPosition, vector<pair<size_t, size_t>> cells, const string color, const size_t blocksIdArg )
    {
        cellState = color;
        blocksId = blocksIdArg;

        for ( auto& cell : cells )
        {
            auto x = startPosition.first + cell.first;
            auto y = startPosition.second + cell.second;
            blockCells.push_back( { x, y } );
            gameField.field[x][y].currentState = color;
            gameField.field[x][y].ownersBlocksId = blocksId;
        }

        canMove = true;
    }

    void TCellsBlock::setRotatePoint( pair<int, int> rotatePointArg )
    {
        rotatePoint = rotatePointArg;
    };

    void TCellsBlock::turn( pair<int, int> rotateVector )
    {
        
    };

    void TCellsBlock::step()
    {
        skip = false;

        for ( auto& cell : blockCells )
        {
            auto [x, y] = cell;
            auto [dx, dy] = moveDirection;

            if ( x + dx >= gameField.field.size() )
            {
                canMove = false;
                break;
            }

            if ( canMove )
                if ( y + dy >= gameField.field[x].size() )
                {
                    skip = true;
                    break;
                }

            const auto fieldBlocksId = gameField.field[x + dx][y + dy].ownersBlocksId;

            if ( ( fieldBlocksId != 0 ) && fieldBlocksId != blocksId )
            {
                cout << fieldBlocksId << endl;
                skip = true;
                checkOverlappingAtNextStep();
                break;
            }
        }

        if ( canMove && !skip )
            checkOverlappingAtNextStep();

        if ( !canMove || skip )
        {
            moveDirection = moveDirectionDefault;
            return;
        }

        for ( auto& cell : blockCells )
        {
            auto [x, y] = cell;
            
            if ( x < gameField.field.size() && ( !gameOverFlag ) )
            {
                cellState = gameField.field[x][y].currentState;
                gameField.field[x][y].currentState = TCellStates::backgroundStateKey;
                gameField.field[x][y].ownersBlocksId = 0;
            }
        }

        auto [dx, dy] = moveDirection;

        for ( auto& cell : blockCells )
        {
            auto& [x, y] = cell;

            x += dx;
            y += dy;

            gameField.field[x][y].currentState = cellState;
            gameField.field[x][y].ownersBlocksId = blocksId;
        }

        rotatePoint.first += dx;
        rotatePoint.second += dy;

        moveDirection = moveDirectionDefault;
    };

    bool TCellsBlock::isGameOver()
    {
        return gameOverFlag;
    };

    bool TCellsBlock::checkOverlappingAtNextStep()
    {
        map<size_t, pair<size_t, size_t>>& borders = lowerBorders;

        if ( moveDirection == vectorLeft )
            borders = leftBorders;

        if ( moveDirection == vectorRight )
            borders = rightBorders;

        for ( auto& cell : borders )
        {
            auto [x, y] = cell.second;
            auto [dx, dy] = moveDirection;

            const auto fieldBlocksId = gameField.field[x + dx][y + dy].ownersBlocksId;

            if ( ( fieldBlocksId != 0 ) && ( fieldBlocksId != blocksId ) )
                skip = true;
        }

        if ( skip && ( moveDirection == vectorDown ) )
            canMove = false;

        return skip;
    };
};
