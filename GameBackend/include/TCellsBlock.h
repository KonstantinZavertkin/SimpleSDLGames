#ifndef _TCELLSBLOCK_H_
#define _TCELLSBLOCK_H_

#include <vector>
#include <string>

#include "TGameField.h"

namespace game_backend
{
    using namespace std;

    class TCellsBlock
    {
        public:
            TCellsBlock( TGameField& gameField );

            ~TCellsBlock();

            void initFigure( pair<size_t, size_t> startPosition, vector<pair<size_t, size_t>> cells, const string color );

            void turn( pair<int, int> rotateVector );

            void step();

            bool isGameOver();
            
            TGameField& gameField;
        
        private:
        
            bool checkOverlappingAtNextStep();
    };
};

#endif // _TCELLSBLOCK_H_