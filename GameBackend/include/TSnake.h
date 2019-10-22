#ifndef _TSNAKE_H_
#define _TSNAKE_H_

#include "TGameField.h"

namespace game_backend
{
    using namespace std;

    class TSnake
    {
        public:
            TSnake( TGameField& gameField );

            ~TSnake();

            void initSnake( pair<size_t, size_t> startPosition, size_t snakeLength );

            void turn( pair<int, int> rotateVector );

            void step();
            
            TGameField& gameField;
            //!< { x, y } -> { lineIndex, columnIndex }
            //!< snakeCells.front() - head
            //!< snakeCells.back() - tail
            deque<pair<size_t, size_t>> snakeCells;
    };
}

#endif
