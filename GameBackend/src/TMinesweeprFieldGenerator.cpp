#include "TMinesweeperFieldGenerator.h"

namespace game_backend 
{
    using namespace std;

    FieldGenerator::FieldGenerator( int sizeX, int sizeY, int amountOfBombs )
        : sizeX( sizeX ), sizeY( sizeY ), amountOfBombs( amountOfBombs )
    {
    }
    void FieldGenerator::prepareArray()
    {
        TMinesweeperCell cell;
        vector<TMinesweeperCell> emptyVector;

        for( int i = 0; i < sizeX; ++i )
            emptyVector.push_back( cell );

        for( int j = 0; j < sizeY; ++j )
            arrayOfCells.push_back( emptyVector );
    };

    void FieldGenerator::putBombs()
    {
        int currentAmount = 0;
        int x, y;

        while( currentAmount < amountOfBombs )
        {
            x = rand() % sizeX;
            y = rand() % sizeY;

            if( !arrayOfCells[y][x].isBomb() )
            {
                arrayOfCells[y][x].putBomb();
                currentAmount++;
            }
        }
    };

    int FieldGenerator::calcBombsInSquare( int x, int y )
    {
        int localAmountOfBombs = 0;

        for( int j = ( x - 1 ); j <= ( x + 1 ); ++j )
        {
            for( int i = ( y - 1 ); i <= ( y + 1 ); ++i )
            {
                if( ( i >= 0 ) && ( i < sizeY ) && ( j >= 0 ) && ( j < sizeX ) )
                {
                    if( arrayOfCells[i][j].isBomb() )
                        ++localAmountOfBombs;
                }
            }
        }

        return localAmountOfBombs;
    };
    void FieldGenerator::calcAmountOfBombsAround()
    {
        for( int i = 0; i < sizeX; ++i )
        {
            for( int j = 0; j < sizeY; ++j )
            {
                arrayOfCells[j][i].setNumOfBombsAround( calcBombsInSquare( i, j ) );
            }
        }
    };

    vector<vector<TMinesweeperCell>>& FieldGenerator::getField()
    {
       return arrayOfCells;
    }
}