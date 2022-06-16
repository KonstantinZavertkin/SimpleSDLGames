#ifndef _TMINESWEEPERBACKEND_H_
#define _TMINESWEEPERBACKEND_H_

#include "TMinesweeperField.h"
#include "TStepAction.h"

namespace game_backend
{
    class TMinesweeperBackend
    {
        public:
            TMinesweeperBackend();
            void initializeField( int sizeX, int sizeY, int amountOfBombs );
            void performStep( int x, int y, char action );
            bool isGameOver();
            Field& getField();

        private:
            Field field;
            TStepAction stepAction;
            int sizeX = 0;
            int sizeY = 0;
            int amountOfBombs = 0;
            bool gameOver = false;
    };
}


#endif // _TMINESWEEPERBACKEND_H_
