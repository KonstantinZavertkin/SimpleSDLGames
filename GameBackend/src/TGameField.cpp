#include "TGameField.h"
#include <iostream>
#include <iomanip>

namespace game_backend
{
    using namespace std;

    TGameField::TGameField( size_t linesCount, size_t columnsCount )
    {
        fieldSize = make_pair( linesCount, columnsCount );
        
        for ( int i = 0; i < fieldSize.first; ++i )
        {
            field.emplace_back();

            for ( int j = 0; j < fieldSize.second; ++j )
            {
                field[i].emplace_back();
                auto& cell = field[i][j];
                cell.ownersBlocksId = 0;
                cell.currentState = TCellStates::backgroundStateKey;
            }
        }
    };

    TGameField::~TGameField()
    {};

    void TGameField::debugPrint()
    {
        cout << "   ";
        
        for ( size_t j = 0; j < field[0].size(); ++j )
        {
            cout << setw(3) << j;
        }

        cout << endl;

        for ( size_t i = 0; i < field.size(); ++i )
        {
            cout << setw( 3 ) << i;
            cout << "|";

            for ( size_t j = 0; j < field[i].size(); ++j )
            {
                auto cell = field[i][j];

                if ( cell.currentState == TCellStates::backgroundStateKey )
                    cout << setw(2) << " ";
                
                if ( cell.currentState == TCellStates::snakeBodyStateKey )
                    cout << setw(2) << "O";
                
                if ( cell.currentState == TCellStates::snakeHeadStateKey )
                    cout << setw(2) << "@";
                
                if ( cell.currentState == TCellStates::snakeTailStateKey )
                    cout << setw(2) << "*";

                cout << "|";
            }

            cout << endl;
        }

        cout << endl;
    }

    void TGameField::scrollField( TCoords direction, optional<size_t> fromLine )
    {
        size_t lastLineIndex = field.size() - 1;

        if ( fromLine )
            lastLineIndex = fromLine.value();

        for ( int i = lastLineIndex; i > 0; --i )
        {
            for ( size_t j = 0; j < fieldSize.second; ++j )
            {
                if ( !field[i][j].canBeMoved || ( field[i][j].currentState == TCellStates::backgroundStateKey ) )
                {
                    if ( !field[i - 1][j].canBeMoved )
                    {
                        field[i][j].canBeMoved = field[i - 1][j].canBeMoved;
                        field[i][j].currentState = field[i - 1][j].currentState;
                        field[i][j].ownersBlocksId = field[i - 1][j].ownersBlocksId;
                    }
                }
            }
        }
    }

    void TGameField::resetField()
    {
        for ( int i = 0; i < fieldSize.first; ++i )
        {
            for ( int j = 0; j < fieldSize.second; ++j )
            {
                auto& cell = field[i][j];
                cell.ownersBlocksId = 0;
                cell.currentState = TCellStates::backgroundStateKey;
            }
        }
    }
}
