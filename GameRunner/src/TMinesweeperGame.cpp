#include "TMinesweeperGame.h"

TMinesweeperGame::TMinesweeperGame( TCoords fieldSize ): gameField( fieldSize.first, fieldSize.second )
{
}

void TMinesweeperGame::gameThread()
{
    bool quitLocal = false;

    while ( !quitLocal )
    {
        syncPoint.lock();
        quitLocal = quit;
        syncPoint.unlock();
        SDL_Delay( 1 );
    }

    syncPoint.lock();
    cout << "Minesweeper game thread done" << endl;
    syncPoint.unlock();
}

void TMinesweeperGame::ioThread()
{
    SDL_Event exitEvent;
    bool pauseLocal = false;
    bool quitLocal = false;

    while ( !quitLocal )
    {
        while ( SDL_PollEvent( &exitEvent ) != 0 )
        {
            if ( exitEvent.type == SDL_QUIT )
            {
                quitLocal = true;
            }

            if ( exitEvent.type == SDL_KEYDOWN )
            {
                auto keyValue = exitEvent.key.keysym.sym;

                //syncPoint.lock();

                //syncPoint.unlock();
            }
        }

        syncPoint.lock();

        quit = quitLocal;
        
        mainDrawer->draw();

        syncPoint.unlock();

        SDL_Delay( 1 );
    }
    syncPoint.lock();
    cout << "Minesweeper io thread done" << endl;
    syncPoint.unlock();
}
