#ifndef _TMINESWEEPERGENERATOR_H_
#define _TMINESWEEPERGENERATOR_H_

#include <vector>
#include "TCell.h"

namespace game_backend 
{
    using namespace std;

    class FieldGenerator
    {
        public:
            FieldGenerator( int x, int y, int amount );
            void prepareArray();
            void putBombs();
            void calcAmountOfBombsAround();
            vector<vector<TMinesweeperCell>>& getField();

        private:
            vector<vector<TMinesweeperCell>> arrayOfCells;

            int sizeX;
            int sizeY;
            int amountOfBombs;
            int calcBombsInSquare( int x, int y );
    };
};

#endif
