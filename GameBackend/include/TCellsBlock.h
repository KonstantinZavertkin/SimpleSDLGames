#ifndef _TCELLSBLOCK_H_
#define _TCELLSBLOCK_H_

#include <vector>
#include <map>
#include <string>

#include "TGameField.h"

namespace game_backend
{
    using namespace std;

    class TCellsBlock
    {
        public:
            TCellsBlock( TGameField& gameField );

            ~TCellsBlock();

            void initFigure( pair<size_t, size_t> startPosition, vector<vector<pair<size_t, size_t>>> cells, const string color );

            void turn( pair<int, int> rotateVector );

            void step();

            bool isGameOver();
            
            TGameField& gameField;

            bool canMove = true;
            bool skip = false;
            bool gameOverFlag = false;
            pair<int, int> moveDirection = { 1, 0 };
            const pair<int, int> moveDirectionDefault = { 1, 0 };

            const pair<int, int> vectorUp = { -1, 0 };
            const pair<int, int> vectorDown = { 1, 0 };
            const pair<int, int> vectorLeft = { 0, -1 };
            const pair<int, int> vectorRight = { 0, 1 };
        
        private:

            vector<vector<pair<size_t, size_t>>> blockCells;   //!< Matrix of cell's coordinates
            map<size_t, pair<size_t, size_t>> leftBorders;
            map<size_t, pair<size_t, size_t>> rightBorders;
            map<size_t, pair<size_t, size_t>> lowerBorders;
            map<size_t, pair<size_t, size_t>> upperBorders;
            string cellState;                                  //! Cell's state


            bool checkOverlappingAtNextStep();

            void updateBordersCells();
    };
};

#endif // _TCELLSBLOCK_H_