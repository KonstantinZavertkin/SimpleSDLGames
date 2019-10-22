#ifndef _TCELL_H_
#define _TCELL_H_

#include <string>

namespace game_backend 
{
    using namespace std;

    class TCellStates
    {
        public:
            static const string snakeHeadStateKey;
            static const string snakeBodyStateKey;
            static const string snakeTailStateKey;
            static const string backgroundStateKey;
            static const string eatStateKey;
    };

    class TCell
    {
        public:
            TCell();
            ~TCell();

            string currentState;
            pair<int, int> moveDirection;          //!< 2-D vector of speed
            pair<int, int> moveDirectionDelta;     //!< dx, dy for next step
            pair<size_t, size_t> thisCoordinates;  //!< { lineIndex; columnIndex }
    };
};

 #endif
