#include "TCellsBlock.h"

namespace game_backend
{
    TCellsBlock::TCellsBlock( TGameField& gameField ) : gameField( gameField )
    {};

    TCellsBlock::~TCellsBlock()
    {};

    void TCellsBlock::initFigure( pair<size_t, size_t> startPosition, vector<pair<size_t, size_t>> cells, const string color )
    {

    };

    void TCellsBlock::turn( pair<int, int> rotateVector )
    {

    };

    void TCellsBlock::step()
    {

    };

    bool TCellsBlock::isGameOver()
    {
        return true;
    };

    bool TCellsBlock::checkOverlappingAtNextStep()
    {
        return true;
    };
};
