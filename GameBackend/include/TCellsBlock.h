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

            void initFigure( pair<size_t, size_t> startPosition, vector<pair<size_t, size_t>> cells, const string color, const size_t blocksId );

            void setRotatePoint( pair<int, int> rotatePoint );

            void turn( pair<int, int> rotateVector );

            void step();

            bool isGameOver();

            const pair<int, int> getRotatePoint() const;
            
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

            vector<pair<int, int>> blockCells;   //!< Matrix of cell's coordinates
            vector<pair<int, int>> blockCellsCopy;   //!< Matrix of cell's coordinates
            string cellState;                                  //! Cell's state

            pair<int, int> rotatePoint;
            size_t blocksId = 0;

            int shiftLeft = 0;
            int shiftRight = 0;
            int shiftBottom = 0;

            bool checkOverlappingAtNextStep();

            void stopFigure();

            void writeCellsToField( const vector<pair<int, int>>& cells );
            void removeFigureFromField( const vector<pair<int, int>>& cells );

            bool tryWriteFigure();
    };
};

#endif // _TCELLSBLOCK_H_