#ifndef _TSNAKEGAME_H_
#define _TSNAKEGAME_H_


#include "TGameField.h"
#include "TCellsChain.h"

namespace game_backend 
{
    using namespace std;

    //! Класс игры "змейка". Создает поле TGameField и связанный с ним объект TCellsChain
    //! Выполняет дискретный шаг игры
    class TSnakeGame
    {
        public:
            TSnakeGame( pair<size_t, size_t> fieldSize, size_t snakeLength );
            ~TSnakeGame();

            bool step();
            void turn( pair<int, int> rotateVector );
            void checkFood();

            TGameField gameField;
            TCellsChain snake;
    };
};

#endif
