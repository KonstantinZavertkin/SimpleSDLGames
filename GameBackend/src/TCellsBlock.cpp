#include <iostream>
#include "TCellsBlock.h"

namespace game_backend
{
    TCellsBlock::TCellsBlock( TGameField& gameField ) : gameField( gameField )
    {};

    TCellsBlock::~TCellsBlock()
    {};

    void TCellsBlock::initFigure( pair<size_t, size_t> startPosition, vector<vector<pair<size_t, size_t>>> cells, const string color, const size_t blocksIdArg )
    {
        cellState = color;
        blocksId = blocksIdArg;

        for ( auto& cellsLine : cells )
        {
            vector<pair<size_t, size_t>> blockCellsLine;

            for ( auto& cell : cellsLine )
            {
                auto x = startPosition.first + cell.first;
                auto y = startPosition.second + cell.second;
                blockCellsLine.push_back( { x, y } );
                gameField.field[x][y].currentState = color;
            }

            blockCells.push_back( blockCellsLine );
        }

        canMove = true;
        updateBordersCells();
    }

    void TCellsBlock::setRotatePoint( pair<int, int> rotatePointArg )
    {
        rotatePoint = rotatePointArg;
    };

    void TCellsBlock::updateBordersCells()
    {
        leftBorders = {};
        rightBorders = {};
        lowerBorders = {};
        upperBorders = {};

        for ( size_t i = 0; i < blockCells.size(); ++i )
        {
            if ( !blockCells[i].empty() )
            {
                leftBorders[i] = blockCells[i][0];
                rightBorders[i] = blockCells[i][blockCells[i].size() - 1];
            }

            for ( size_t j = 0; j < blockCells[i].size(); ++j )
            {
                auto [lineCoord, columnCoord] = blockCells[i][j];

                if ( lowerBorders.find( columnCoord ) != lowerBorders.end() )
                {
                    if ( lowerBorders[columnCoord].first < lineCoord )
                        lowerBorders[columnCoord] = { lineCoord, columnCoord };
                }
                else
                    lowerBorders[columnCoord] = { lineCoord, columnCoord };
                
            }
        }
    };

    void TCellsBlock::turn( pair<int, int> rotateVector )
    {
        
    };

    void TCellsBlock::step()
    {
        skip = false;

        for ( auto& cellsLine : blockCells )
            for ( auto& cell : cellsLine )
            {
                auto [x, y] = cell;
                auto [dx, dy] = moveDirection;

                if ( x + dx >= gameField.field.size() )
                    canMove = false;
                
                if ( canMove )
                    if ( y + dy >= gameField.field[x].size() )
                        skip = true;
            }

        if ( canMove && !skip )
        {
            updateBordersCells();
            checkOverlappingAtNextStep();
        }

        if ( !canMove || skip )
        {
            moveDirection = moveDirectionDefault;
            return;
        }

        for ( auto& cellsLine : blockCells )
            for ( auto& cell : cellsLine )
            {
                auto [x, y] = cell;
                
                if ( x < gameField.field.size() && ( !gameOverFlag ) )
                {
                    cellState = gameField.field[x][y].currentState;
                    gameField.field[x][y].currentState = TCellStates::backgroundStateKey;
                }
            }

        auto [dx, dy] = moveDirection;

        for ( auto& cellsLine : blockCells )
            for ( auto& cell : cellsLine )
            {
                auto& [x, y] = cell;

                x += dx;
                y += dy;

                gameField.field[x][y].currentState = cellState;
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

            if ( gameField.field[x + dx][y + dy].currentState != TCellStates::backgroundStateKey )
                skip = true;
        }

        if ( skip && ( moveDirection == vectorDown ) )
            canMove = false;

        return skip;
    };
};
