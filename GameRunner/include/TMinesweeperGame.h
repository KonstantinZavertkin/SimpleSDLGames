#ifndef _TMINESWEEPERGAME_H_
#define _TMINESWEEPERGAME_H_

#include <mutex>
#include "TMinesweeperBackend.h"
#include "TDrawer.h"

using namespace game_backend;

class TMinesweeperGame
{
    public:
        TMinesweeperGame( TCoords fieldSize );

        void gameThread();
        void ioThread();

        TMinesweeperBackend minesweeper;
        TGameField gameField;

        TDrawer* mainDrawer = nullptr;
        TFontDrawer* scorePrinter = nullptr;
        TCellRectangles* cellRectangles = nullptr;
        TFontDrawer* gameStatus = nullptr;

        TCoords fieldSize;

    private:
        mutex syncPoint;
        bool quit = false;
};

#endif // _TMINESWEEPERGAME_H_
