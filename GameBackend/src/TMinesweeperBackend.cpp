#include "TMinesweeperBackend.h"
#include "TMinesweeperField.h"
#include "TStepAction.h"

namespace game_backend
{
    void TMinesweeperBackend::initializeField( int sizeX, int sizeY, int amountOfBombs )
    {
        gameOver = false;
        Field field;
        field.createField( sizeX, sizeY, amountOfBombs );
        this -> field = field;
        TStepAction stepAction;
        stepAction.initialStepAction( sizeX, sizeY, field );
        this->stepAction = stepAction;
    };

    void TMinesweeperBackend::performStep( int x, int y, char action )
    {
        stepAction.performAction( x, y, action );
        field = stepAction.getField();
    };

    bool TMinesweeperBackend::isGameOver()
    {
        return gameOver;
    };

    Field TMinesweeperBackend::getField()
    {
        return field;
    };
}
