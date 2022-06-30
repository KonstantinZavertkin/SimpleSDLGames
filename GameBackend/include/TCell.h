#ifndef _TCELL_H_
#define _TCELL_H_

#include <string>
#include "CommonTypes.hpp"

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
            static const string newSectionStateKey;

            static const string redColorStateKey;
            static const string greenColorStateKey;
            static const string blueColorStateKey;
            static const string cyanColorStateKey;
            static const string magentaColorStateKey;
            static const string yellowColorStateKey;
            static const string orangeColorStateKey;

            static const string virtualFigure;
    };

    class TCell
    {
        public:
            TCell();
            virtual ~TCell();

            string currentState;
            size_t ownersBlocksId = 0;
            bool canBeMoved = false;
    };

    class TExtendedCell : public TCell
    {
        public:
            TExtendedCell(){};
            ~TExtendedCell(){};

            TCoords moveDirection;          //!< 2-D vector of speed
            TCoords moveDirectionDelta;     //!< dx, dy for next step
            TCoords thisCoordinates;        //!< { lineIndex; columnIndex }
    };

    class TMinesweeperCell : public TCell
    {
        public:
            TMinesweeperCell();
            bool isBomb();
            bool isOpened();
            bool isFlag();
            int getNumOfBombsAround();
            void putBomb();
            void changeFlag();
            void setOpened();
            void setNumOfBombsAround( int amount );

        private:
            bool opened = false;
            bool bomb = false;
            bool flag = false;
            int amountOfBombsAround = 0;
    };
};

 #endif
