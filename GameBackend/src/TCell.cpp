
#include "TCell.h"

namespace game_backend 
{
    const std::string TCellStates::eatStateKey = "eat";
    const std::string TCellStates::backgroundStateKey = "background";
    const std::string TCellStates::snakeHeadStateKey = "snakeHead";
    const std::string TCellStates::snakeBodyStateKey = "snakeBody";
    const std::string TCellStates::snakeTailStateKey = "snakeTail";

    TCell::TCell() : currentState( TCellStates::backgroundStateKey ){};

    TCell::~TCell(){};
};
