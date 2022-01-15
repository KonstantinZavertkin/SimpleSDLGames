#ifndef _TCELLSBLOCK_H_
#define _TCELLSBLOCK_H_

#include <vector>
#include <map>
#include <string>

#include "CommonTypes.hpp"
#include "TGameField.h"

namespace game_backend
{
    using namespace std;

    class TCellsBlock
    {
        public:
            TCellsBlock( TGameField& gameField );

            ~TCellsBlock();

            void initFigure( TCoords startPosition, vector<TCoords> cells, const string color, const size_t blocksId );

            void setRotatePoint( TCoords rotatePoint );

            void turn( TCoords rotateVector );

            void step();

            bool isGameOver() const;

            void clearVirtual();

            void makeVirtual();

            const TCoords getRotatePoint() const;
            
            TGameField& gameField;

            bool canMove = true;
            bool gameOverFlag = false;
            TCoords moveDirection = { 1, 0 };
            const TCoords moveDirectionDefault = { 1, 0 };

            
        
        //private:

            vector<TCoords> blockCells;   //!< Matrix of cell's coordinates
            vector<TCoords> blockCellsCopy;   //!< Matrix of cell's coordinates
            string cellState;                                  //! Cell's state

            TCoords rotatePoint;
            size_t blocksId = 0;

            int shiftLeft = 0;
            int shiftRight = 0;
            int shiftTop = 0;
            int shiftBottom = 0;

            void stopFigure();

            void writeCellsToField( const vector<TCoords>& cells );
            void removeFigureFromField( const vector<TCoords>& cells );

            bool tryWriteFigure();
    };
};

#endif // _TCELLSBLOCK_H_