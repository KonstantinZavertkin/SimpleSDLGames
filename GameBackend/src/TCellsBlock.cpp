#include <iostream>
#include "TCellsBlock.h"

namespace game_backend
{
    TCellsBlock::TCellsBlock( TGameField& gameField ) : gameField( gameField )
    {};

    TCellsBlock::~TCellsBlock()
    {};

    void TCellsBlock::initFigure( pair<size_t, size_t> startPosition, vector<pair<size_t, size_t>> cells, const string color )
    {
        for ( const auto& cell : cells )
        {
            auto x = startPosition.first + cell.first;
            auto y = startPosition.second + cell.second;
            blockCells.push_back( { x, y } );
            gameField.field[x][y].currentState = color;
            gameField.field[x][y].moveDirection = make_pair( 1, 0 );
        }
    };

    void TCellsBlock::turn( pair<int, int> rotateVector )
    {

    };

    void TCellsBlock::step()
    {
        bool canMove = true;
        string state;
        vector<pair<size_t, size_t>> blockCellsCopy = vector<pair<size_t, size_t>>( blockCells );

        moveDirection = { 1, 0 };

        for ( auto& cell : blockCellsCopy )
        {
            auto [x, y] = cell;

            if ( x + moveDirection.first >= gameField.field.size() )
                canMove = false;
            
            if ( canMove )
                if ( y + moveDirection.second >= gameField.field.size() )
                {
                    canMove = false;
                }
            
        }

        if ( !canMove )
            return;

        for ( auto& cell : blockCells )
        {
            auto x = cell.first;
            auto y = cell.second;
            
            if ( x < gameField.field.size() && (!gameOverFlag) )
            {
                state = gameField.field[x][y].currentState;
                gameField.field[x][y].currentState = TCellStates::backgroundStateKey;
            }
        }

        for ( auto& cell : blockCells )
        {
            //cell.first++;
            //cell.second++;
            auto x = cell.first;
            auto y = cell.second;

            if ( x + 1 < gameField.field.size() )
            {
                cell.first++;
                x = cell.first;
                gameField.field[x][y].currentState = state;
            }
            else
                gameOverFlag = true;
        }
    };

    bool TCellsBlock::isGameOver()
    {
        return gameOverFlag;
    };

    bool TCellsBlock::checkOverlappingAtNextStep()
    {
        return true;
    };
};
