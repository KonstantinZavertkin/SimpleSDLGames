
#include "TCell.h"

namespace game_backend 
{
    const std::string TCellStates::eatStateKey = "eat";
    const std::string TCellStates::backgroundStateKey = "background";
    const std::string TCellStates::snakeHeadStateKey = "snakeHead";
    const std::string TCellStates::snakeBodyStateKey = "snakeBody";
    const std::string TCellStates::snakeTailStateKey = "snakeTail";
    const std::string TCellStates::newSectionStateKey = "snakeNewSection";

    const std::string TCellStates::redColorStateKey = "redColor";
    const std::string TCellStates::greenColorStateKey = "greenColor";
    const std::string TCellStates::blueColorStateKey = "blueColor";

    const std::string TCellStates::cyanColorStateKey = "cyanColor";
    const std::string TCellStates::magentaColorStateKey = "magentaColor";
    const std::string TCellStates::yellowColorStateKey = "yellowColor";
    const std::string TCellStates::orangeColorStateKey = "orangeColor";

    const std::string TCellStates::virtualFigure = "virtualFigure";

    TCell::TCell() : currentState( TCellStates::backgroundStateKey ){};

    TCell::~TCell(){}

    TMinesweeperCell::TMinesweeperCell()
    {
    }

    bool TMinesweeperCell::isBomb()
    {
        return bomb;
    }

    bool TMinesweeperCell::isOpened()
    {
        return opened;
    }

    bool TMinesweeperCell::isFlag()
    {
        return flag;
    }

    int TMinesweeperCell::getNumOfBombsAround()
    {
        return amountOfBombsAround;
    }

    void TMinesweeperCell::putBomb()
    {
        bomb = true;
    }

    void TMinesweeperCell::changeFlag()
    {
        flag = !flag;
    }

    void TMinesweeperCell::setOpened()
    {
        opened = true;
    }

    void TMinesweeperCell::setNumOfBombsAround( int amount )
    {
        amountOfBombsAround = amount;
    };
};
