#ifndef _TMINESWEEPERFIELD_H_
#define _TMINESWEEPERFIELD_H_

#include<vector>
#include "TCell.h"
#include "TMinesweeperFieldGenerator.h"

namespace game_backend
{
    using namespace std;

    class Field
    {
        public:
            void createField( int sizeX, int sizeY, int amountOfBombs );
            void changeFlag( int x, int y );
            void setOpened( int x, int y );
            int getValue( int x, int y );
            bool isOpened( int x, int y );
            bool isBomb( int x, int y );
            bool isFlag( int x, int y );
            bool isBombOpened() const;
            bool isWholeFieldOpened();
            vector<vector<TMinesweeperCell>>& getField();
            void openAllBombs();

        private:
            vector<vector<TMinesweeperCell>> field;
            int sizeX = 0;
            int sizeY = 0;
            int amountOfBombs = 0;
            bool bombOpened = false;
    };
}

#endif // _TMINESWEEPERFIELD_H_
