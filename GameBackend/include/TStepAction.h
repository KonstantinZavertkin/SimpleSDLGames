#ifndef _TSTEPACTION_H_
#define _TSTEPACTION_H_

#include <iostream>
#include "TMinesweeperField.h"

namespace game_backend
{
    class TStepAction
    {
        public:
            TStepAction( Field& field );
            void initialStepAction( int sizeX, int sizeY );
            void performAction( int x, int y, char currentAction );
            void changeFlag( int x, int y );
            void openCells( int x, int y );
            Field& getField();

        private:
            Field& field;
            int sizeX = 0;
            int sizeY = 0;
            char currentAction = '\0';
            int getAmountOfFlagsInSquare( int x, int y );
            void tryOpen( int x, int y );
    };
}


#endif
