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

            void initCellsChain( pair<size_t, size_t> startPosition, size_t snakeLength );

            void turn( pair<int, int> rotateVector );

            void step();

            bool isGameOver();
            
            TGameField& gameField;
            //!< { x, y } -> { lineIndex, columnIndex }
            //!< snakeCells.front() - head
            //!< snakeCells.back() - tail
            deque<pair<size_t, size_t>> snakeCells;

        private:
            void updateSnakeHeadAndTail();
            bool gameOverFlag = false;
    };
}

#endif
