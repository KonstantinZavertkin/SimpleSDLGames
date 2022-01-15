#ifndef _TCellsChain_H_
#define _TCellsChain_H_

#include "TGameField.h"

namespace game_backend
{
    using namespace std;

    class TCellsChain
    {
        public:
            TCellsChain( TGameField& gameField );

            ~TCellsChain();

            void initCellsChain( TCoords startPosition, size_t snakeLength );

            void turn( TCoords rotateVector );

            void step();

            bool isGameOver();
            
            TGameField& gameField;
            //!< { x, y } -> { lineIndex, columnIndex }
            //!< snakeCells.front() - head
            //!< snakeCells.back() - tail
            deque<TExtendedCell> snakeCells;

        private:
            bool gameOverFlag = false;
    };
}

#endif
