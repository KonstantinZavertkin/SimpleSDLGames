#include "TMinesweeperField.h"

namespace game_backend
{
    void Field::createField( int sizeX, int sizeY, int amountOfBombs )
    {
        this->sizeX = sizeX;
        this->sizeY = sizeY;
        this->amountOfBombs = amountOfBombs;
        bombOpened = false;

        FieldGenerator generatedField( sizeX, sizeY, amountOfBombs );
        generatedField.prepareArray();
        generatedField.putBombs();
        generatedField.calcAmountOfBombsAround();
        field = generatedField.getField();
    }

    void Field::changeFlag( int x, int y )
    {
        field[y][x].changeFlag();
    };

    void Field::setOpened( int x, int y )
    {
        field[y][x].setOpened();

        if ( field[y][x].isBomb() )
           bombOpened = true;
    };

    bool Field::isBomb( int x, int y )
    {
        return field[y][x].isBomb();
    };

    bool Field::isOpened( int x, int y )
    {
        return field[y][x].isOpened();
    }

    int Field::getValue( int x, int y )
    {
        return field[y][x].getNumOfBombsAround();
    }

    bool Field::isFlag( int x, int y )
    {
        return field[y][x].isFlag();
    }

    bool Field::isBombOpened() const
    {
        return bombOpened;
    }

    bool Field::isWholeFieldOpened()
    {
        const int cellsCount = sizeX * sizeY;
        int openedCellsCount = 0;

        for ( auto& line : field )
           for ( auto& cellRef : line )
               if ( cellRef.isOpened() )
                  ++openedCellsCount;

        if ( openedCellsCount == cellsCount - amountOfBombs )
           return true;

        return false;
    };

    vector<vector<TMinesweeperCell>>& Field::getField()
    {
        return field;
    };
}

