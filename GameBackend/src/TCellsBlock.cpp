﻿#include <iostream>
#include "TCellsBlock.h"

#include <algorithm>

namespace game_backend
{
    TCellsBlock::TCellsBlock( TGameField& gameField ) : gameField( gameField )
    {}

    TCellsBlock::~TCellsBlock()
    {};

    void TCellsBlock::initFigure( TCoords startPosition, vector<TCoords> cells, const string color, const size_t blocksIdArg )
    {
        cellState = color;
        blocksId = blocksIdArg;

        const auto [dx, dy] = startPosition;

        for ( auto& cell : cells )
        {
            auto [x, y] = make_pair( cell.first + dx, cell.second + dy );

            if ( gameField.field[x][y].ownersBlocksId != 0 && gameField.field[x][y].ownersBlocksId != blocksId )
                gameOverFlag = true;

            blockCells.emplace_back( x, y );
            gameField.field[x][y].currentState = color;
            gameField.field[x][y].ownersBlocksId = blocksId;
            gameField.field[x][y].canBeMoved = true;
        }

        canMove = true;

        setRotatePoint( { 1, startPosition.second + 1 } );
    }

    void TCellsBlock::setRotatePoint( TCoords rotatePointArg )
    {
        rotatePoint = rotatePointArg;
    };

    void TCellsBlock::turn( TCoords rotateVector )
    {
        if ( !canMove )
            return;

        blockCellsCopy = vector( blockCells );

        shiftLeft = 0;
        shiftTop = 0;
        shiftRight = gameField.fieldSize.second - 1;
        shiftBottom = gameField.fieldSize.first - 1;

        //! Rotate the figure without checking boundaries
        for ( size_t i = 0; i < blockCells.size(); ++i )
        {
            auto& [x, y] = blockCells[i];
            auto [rx, ry] = rotatePoint;

            int newX = static_cast<int>( rx ) - ( y - ry );
            int newY = static_cast<int>( ry ) + ( x - rx );

            //! Save shifts to place whole figure in fields boundaries 
            shiftTop = std::min( shiftTop, newX );
            shiftBottom = std::max( shiftBottom, newX );
            shiftLeft = std::min( shiftLeft, newY );
            shiftRight = std::max( shiftRight, newY );

            blockCells[i] = { newX, newY };
        }

        shiftBottom -= ( gameField.fieldSize.first - 1 );
        shiftRight -= ( gameField.fieldSize.second - 1 );

        rotatePoint.first += std::abs( shiftTop );
        rotatePoint.second += std::abs( shiftLeft );
        rotatePoint.first -= std::abs( shiftBottom );
        rotatePoint.second -= std::abs( shiftRight );

        tryWriteFigure();
    };

    void TCellsBlock::step()
    {
        if ( !canMove || gameOverFlag )
            return;

        blockCellsCopy = vector( blockCells );

        auto [dx, dy] = moveDirection;

        for ( auto& cell : blockCells )
        {
            auto& [x, y] = cell;

            x += dx;
            y += dy;
        }

        if ( !tryWriteFigure() )
        {
            rotatePoint.first += dx;
            rotatePoint.second += dy;
        }
        else
            if ( moveDirection == moveDirectionDefault )
                stopFigure();

        moveDirection = moveDirectionDefault;
    };

    bool TCellsBlock::isGameOver() const
    {
        return gameOverFlag;
    }

    void TCellsBlock::clearVirtual()
    {
        for ( auto& line : gameField.field )
            for ( auto& cell : line )
                if ( cell.currentState == TCellStates::virtualFigure )
                {
                    cell.currentState = TCellStates::backgroundStateKey;
                    cell.ownersBlocksId = 0;
                    cell.canBeMoved = false;
                }
    }

    void TCellsBlock::makeVirtual()
    {
        cellState = TCellStates::virtualFigure;
    }

    const TCoords TCellsBlock::getRotatePoint() const
    {
        return rotatePoint;
    }

    void TCellsBlock::stopFigure()
    {
        canMove = false;

        for ( const auto& cell : blockCells )
        {
            const auto [x, y] = cell;
            gameField.field[x][y].canBeMoved = false;
        }
    }

    void TCellsBlock::writeCellsToField( const vector<TCoords>& cells )
    {
        for ( const auto& cell : cells )
        {
            const auto [newX, newY] = cell;

            gameField.field[newX][newY].ownersBlocksId = blocksId;
            gameField.field[newX][newY].currentState = cellState;
            gameField.field[newX][newY].canBeMoved = true;
        }
    }

    void TCellsBlock::removeFigureFromField( const vector<TCoords>& cells )
    {
        for ( const auto& cell : cells )
        {
            const auto [x, y] = cell;

            gameField.field[x][y].ownersBlocksId = 0;
            gameField.field[x][y].currentState = TCellStates::backgroundStateKey;
            gameField.field[x][y].canBeMoved = false;
        }
    }

    bool TCellsBlock::tryWriteFigure()
    {
        bool cantPlaceFigure = false;

        //! Write figure in the blockCells considering bounds checks 
        for ( auto& cell : blockCells )
        {
            auto [newX, newY] = cell;

            if ( shiftLeft != 0 )
                newY += std::abs( shiftLeft );
                
            if ( shiftRight != 0 )
                newY -= std::abs( shiftRight );

            if ( shiftTop != 0 )
                newX += std::abs( shiftTop );

            if ( shiftBottom != 0 )
                newX -= std::abs( shiftBottom );

            cell = { newX, newY };

            if ( newX < 0 || newY < 0 )
            {
                cantPlaceFigure = true;
                break;
            }

            if ( newX >= gameField.fieldSize.first || newY >= gameField.fieldSize.second )
            {
                cantPlaceFigure = true;
                break;
            }

            if ( gameField.field[newX][newY].ownersBlocksId != 0 && gameField.field[newX][newY].ownersBlocksId != blocksId )
            {
                cantPlaceFigure = true;
                break;
            }
        }

        shiftLeft = 0;
        shiftTop = 0;
        shiftRight = 0;
        shiftBottom = 0;

        if ( !cantPlaceFigure )
        {
            removeFigureFromField( blockCellsCopy );
            writeCellsToField( blockCells );
        }
        else
            blockCells = blockCellsCopy;

        return cantPlaceFigure;
    };
};
