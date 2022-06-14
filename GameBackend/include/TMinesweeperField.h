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
            vector<vector<TMinesweeperCell>>& getField();

        private:
            vector<vector<TMinesweeperCell>> field;
            int sizeX = 0;
            int sizeY = 0;
            int amountOfBombs = 0;
    };
}

#endif // _TMINESWEEPERFIELD_H_
