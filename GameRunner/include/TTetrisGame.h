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
#include "TScoreStorage.h"
#include "TMainMenu.h"

using namespace std;
using namespace game_backend;

class TTetrisGame
{
    public:
        TTetrisGame( TCoords fieldSize );
        ~TTetrisGame();

        void initGame();

        void gameThread();
        void ioThread();

        TTetrisBackend tetrisBackend;

        TDrawer* mainDrawer = nullptr;
        TFontDrawer* scorePrinter = nullptr;
        TFontDrawer* bestScorePrinter = nullptr;
        TMainMenu* pauseMenu = nullptr;
        TMainMenu* gameOverMenu = nullptr;

    private:
        
        mutex syncPoint;
        const string pathToBestScoreFile = "tetris_best_score.txt";
        TScoreStorage bestScoreStorage;
        unsigned bestScore = 0;
        unsigned currentScore = 0;
};

#endif
