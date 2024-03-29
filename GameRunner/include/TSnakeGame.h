#ifndef _TSNAKEGAME_H_
#define _TSNAKEGAME_H_

#include <deque>
#include <mutex>

#include "TGameField.h"
#include "TCellsChain.h"
#include "TDrawer.h"
#include "TFieldDrawer.h"
#include "TMainMenu.h"
#include "TSnakeBackend.h"

using namespace std;

//! Класс игры "змейка". Создает поле TGameField и связанный с ним объект TCellsChain
//! Выполняет дискретный шаг игры
class TSnakeGame
{
    public:
        TSnakeGame( TCoords fieldSize, size_t snakeLength );
        ~TSnakeGame();

        void runGame();

        void gameThread();
        void ioThread();

        TSnakeBackend gameBackend;

        TDrawer* mainDrawer = nullptr;
        TFontDrawer* scorePrinter = nullptr;
        TFontDrawer* bestScorePrinter = nullptr;
        TMainMenu* pauseMenu = nullptr;

    private:
        mutex syncPoint;
        
};

#endif
