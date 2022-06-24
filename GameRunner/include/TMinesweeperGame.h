#ifndef _TMINESWEEPERGAME_H_
#define _TMINESWEEPERGAME_H_

#include <mutex>
#include <ctime>
#include "TMinesweeperBackend.h"
#include "TDrawer.h"
#include "TMainMenu.h"
#include "TScoreStorage.h"

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
        TFontDrawer* gameTitle = nullptr;
        TFontDrawer* gameStatus = nullptr;
        TFontDrawer* flagsCountDrawer= nullptr;
        TFontDrawer* timeDrawer = nullptr;
        TFontDrawer* secondsDrawer = nullptr;
        TFontDrawer* bestTimeDrawer = nullptr;
        TMainMenu* pauseMenu = nullptr;

        TCoords fieldSize;

    private:
        mutex syncPoint;
        bool quit = false;
        time_t startTime = 0;
        double seconds = 0;
        double secondsPause = 0;
        bool startTimeFlag = false;

        const string pathToBestScoreFile = "minesweeper_best_time.txt";
        TScoreStorage bestScoreStorage;
        unsigned bestScore = 0;
        unsigned currentScore = 0;
};

#endif // _TMINESWEEPERGAME_H_
