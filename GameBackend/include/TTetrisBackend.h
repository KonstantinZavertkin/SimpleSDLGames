#ifndef _TTETRIS_BACKEND_H_
#define _TTETRIS_BACKEND_H_

#include <deque>
#include <memory>
#include <optional>

#include "CommonTypes.hpp"
#include "TCellsBlock.h"
#include "TGameField.h"

namespace game_backend
{
    class TTetrisBackend
    {
        public:
            TTetrisBackend( TCoords fieldSize );
            ~TTetrisBackend();

            std::optional<size_t> checkFullLines() const;

            void createFigure();

            void createFigureIfRequired();

            void showBlockShadow();

            void gameStep();

            size_t getTimeToSleep();

            void reset();

            TGameField gameField;
            TGameField nextFigureField;

            std::deque<TCellsBlock> allBlocks;

            std::unique_ptr<TCellsBlock> virtualBlock;

            size_t figureId = 0;
            size_t currentFigureId = 0;
            size_t nextFigureId = 0;
            bool pauseGame = false;
            bool quit = false;
            bool gameOver = false;

            size_t gameScore = 0;
            bool isAccelerate = true;

        private:
            const size_t mainTimeToSleep = 500;
            const size_t scrollTimeToSleep = mainTimeToSleep / 4;
            size_t gameScoreDelta = 0;
            size_t realTimeToSleep = mainTimeToSleep;
            size_t currentTimeToSleep = mainTimeToSleep;
            size_t figuresCounter = 0;
            size_t prevFiguresCounter = 0;
            TCoords fieldSize;
    };
}

#endif
