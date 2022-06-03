#ifndef _TTETRISGAME_H_
#define _TTETRISGAME_H_

#include <cstddef>
#include <utility>
#include <deque>
#include <mutex>
#include <optional>

#include "TDrawer.h"
#include "TGameField.h"
#include "TCellsBlock.h"
#include "TFieldDrawer.h"
#include "TFontDrawer.h"
#include "TTetrisBackend.h"

using namespace std;
using namespace game_backend;

class TTetrisGame
{
    public:
        TTetrisGame( TCoords fieldSize );
        ~TTetrisGame();

        void gameThread();
        void ioThread();

        TTetrisBackend tetrisBackend;

        //TFieldDrawer* mainFieldDrawer = nullptr;
        //TFieldDrawer* nextFigureFieldDrawer = nullptr;
        TDrawer* mainDrawer;
        TFontDrawer* scorePrinter = nullptr;

    private:
        mutex syncPoint;
};

#endif
