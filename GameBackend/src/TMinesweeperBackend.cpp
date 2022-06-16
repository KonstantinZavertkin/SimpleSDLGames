#include "TMinesweeperBackend.h"
#include "TMinesweeperField.h"
#include "TStepAction.h"

namespace game_backend
{
    TMinesweeperBackend::TMinesweeperBackend() : stepAction( field )
    {
    }

    void TMinesweeperBackend::initializeField( int sizeX, int sizeY, int amountOfBombs )
    {
        gameOver = false;
        field.createField( sizeX, sizeY, amountOfBombs );
        stepAction.initialStepAction( sizeX, sizeY );
    };

    void TMinesweeperBackend::performStep( int x, int y, char action )
    {
        stepAction.performAction( x, y, action );
        field = stepAction.getField();

        if ( field.isBombOpened() )
           gameOver = true;
    };

    bool TMinesweeperBackend::isGameOver()
    {
        return gameOver;
    }

    bool TMinesweeperBackend::isWin()
    {
        return field.isWholeFieldOpened();
    };

    Field& TMinesweeperBackend::getField()
    {
        return field;
    };
}
