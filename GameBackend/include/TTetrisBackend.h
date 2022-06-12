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

            std::optional<size_t> checkFullLines();

            void createFigure();

            void createFigureIfRequired();

            void showBlockShadow();

            void gameStep();

            TGameField gameField;
            TGameField nextFigureField;

            std::deque<TCellsBlock> allBlocks;

            std::unique_ptr<TCellsBlock> virtualBlock;

            size_t figureId = 0;
            size_t currentFigureId = 0;
            size_t nextFigureId = 0;
            bool pauseGame = false;
            bool quit = false;

            size_t gameScore = 0;
            size_t gameScoreDelta = 0;
            size_t timeToSleep = 500;
    };
}

#endif
