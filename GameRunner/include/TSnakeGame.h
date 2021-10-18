#ifndef _TSNAKEGAME_H_
#define _TSNAKEGAME_H_

#include <deque>
#include <mutex>

#include "TGameField.h"
#include "TCellsChain.h"
#include "TFieldDrawer.h"

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

        void gameThread();
        void ioThread();

        game_backend::TGameField gameField;
        game_backend::TCellsChain snake;

        TFieldDrawer* fDrawer;

        size_t clockCounter = 0;
        bool performStep = true;
        bool pauseGame = false;
        bool quit = false;

        deque<pair<int, int>> rotationsQueue;

        mutex syncPoint;
        
};

#endif
