#ifndef _TSNAKEBACKEND_H_
#define _TSNAKEBACKEND_H_
#include "TCellsChain.h"
#include "TGameField.h"
#include "include/TScoreStorage.h"

namespace game_backend
{
    class TSnakeBackend
    {
        public:
            TSnakeBackend( TCoords fieldSize, size_t snakeLength );

            bool step();
            void turn( TCoords rotateVector );
            void checkFood();

            TGameField gameField;
            TCellsChain snake;

            deque<TCoords> rotationsQueue;

            size_t initSnakeLength = 0;
        
            const string pathToBestScoreFile = "snake_best_score.txt";
            TScoreStorage bestScoreStorage;
            unsigned bestScore = 0;
            unsigned currentScore = 0;
    };
}
#endif // _TSNAKEBACKEND_H_
