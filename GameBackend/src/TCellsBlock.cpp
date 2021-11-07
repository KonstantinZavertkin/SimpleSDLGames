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
            gameField.field[x][y].canBeMoved = true;
        }

        canMove = true;

        setRotatePoint( { 1, startPosition.second + 1 } );
    }

    void TCellsBlock::setRotatePoint( pair<int, int> rotatePointArg )
    {
        rotatePoint = rotatePointArg;
    };

    void TCellsBlock::turn( pair<int, int> rotateVector )
    {
        if ( !canMove )
            return;

        blockCellsCopy = vector( blockCells );

        shiftLeft = 0;
        shiftRight = 0;
        shiftTop = 0;
        shiftBottom = 0;

        //! Rotate the figure without checking boundaries
        for ( size_t i = 0; i < blockCells.size(); ++i )
        {
            auto& [x, y] = blockCells[i];
            auto [rx, ry] = rotatePoint;

            int newX = static_cast<int>( rx ) - ( y - ry );
            int newY = static_cast<int>( ry ) + ( x - rx );

            if ( newX < 0 )
                if ( newX < shiftTop )
                    shiftTop = newX;

            if ( newX >= gameField.fieldSize.first )
                if ( newX > shiftBottom )
                    shiftBottom = newX;

            if ( newY < 0 )
                if ( newY < shiftLeft )
                    shiftLeft = newY;

            if ( newY >= gameField.fieldSize.second )
                if ( newY > shiftRight )
                    shiftRight = newY;

            blockCells[i] = { newX, newY };
        }

        if ( shiftTop != 0 )
            rotatePoint.first += std::abs( shiftTop );

        if ( shiftBottom != 0 )
        {
            shiftBottom -= ( gameField.fieldSize.first - 1 );
            rotatePoint.first -= std::abs( shiftBottom );
        }

        if ( shiftLeft != 0 )
            rotatePoint.second += std::abs( shiftLeft );
        
        if ( shiftRight != 0 )
        {
            shiftRight -= gameField.fieldSize.second - 1;
            rotatePoint.second -= std::abs( shiftRight );
        }

        tryWriteFigure();
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
                stopFigure();
                break;
            }

            if ( canMove )
                if ( y + dy >= gameField.field[x].size() )
                {
                    skip = true;
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
                gameField.field[x][y].canBeMoved = false;
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
            gameField.field[x][y].canBeMoved = true;
        }

        rotatePoint.first += dx;
        rotatePoint.second += dy;

        moveDirection = moveDirectionDefault;
    };

    bool TCellsBlock::isGameOver() const
    {
        return gameOverFlag;
    }

    const pair<int, int> TCellsBlock::getRotatePoint() const
    {
        return rotatePoint;
    };

    bool TCellsBlock::checkOverlappingAtNextStep()
    {
        for ( auto& cell : blockCells )
        {
            auto [x, y] = cell;
            auto [dx, dy] = moveDirection;

            const auto fieldBlocksId = gameField.field[x + dx][y + dy].ownersBlocksId;

            if ( ( fieldBlocksId != 0 ) && ( fieldBlocksId != blocksId ) )
                skip = true;
        }

        if ( skip && ( moveDirection == vectorDown ) )
            stopFigure();

        return skip;
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

    void TCellsBlock::writeCellsToField( const vector<pair<int, int>>& cells )
    {
        for ( const auto& cell : cells )
        {
            const auto [newX, newY] = cell;

            gameField.field[newX][newY].ownersBlocksId = blocksId;
            gameField.field[newX][newY].currentState = cellState;
            gameField.field[newX][newY].canBeMoved = true;
        }
    }

    void TCellsBlock::removeFigureFromField( const vector<pair<int, int>>& cells )
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

            if ( gameField.field[newX][newY].ownersBlocksId != 0 && gameField.field[newX][newY].ownersBlocksId != blocksId )
            {
                cantPlaceFigure = true;
                break;
            }
        }

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
