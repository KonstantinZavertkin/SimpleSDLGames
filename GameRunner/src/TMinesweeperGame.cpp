#include "TMinesweeperGame.h"

TMinesweeperGame::TMinesweeperGame( TCoords fieldSize ): gameField( fieldSize.first, fieldSize.second )
{
    this->fieldSize = fieldSize;
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
    std::cout << "Minesweeper game thread done" << endl;
    syncPoint.unlock();
}

void TMinesweeperGame::ioThread()
{
    SDL_Event event;
    bool pauseLocal = false;
    bool quitLocal = false;

    while ( !quitLocal )
    {
        while ( SDL_PollEvent( &event ) != 0 )
        {
            if ( event.type == SDL_QUIT )
            {
                quitLocal = true;
            }

            if ( event.type == SDL_KEYDOWN )
            {
                cout << minesweeper.isGameOver() << endl;
            }

            if ( event.type == SDL_MOUSEBUTTONDOWN )
            {
                const auto x = event.button.x;
                const auto y = event.button.y;

                syncPoint.lock();

                if ( const auto cellCoords = cellRectangles->getCellCoords( x, y ) )
                {
                    const auto [cx, cy] = *cellCoords;

                    cout << cx << ", " << cy << endl;

                    if ( event.button.button == SDL_BUTTON_LEFT )
                        minesweeper.performStep( cy, cx, 'a' );

                    if ( event.button.button == SDL_BUTTON_RIGHT )
                        minesweeper.performStep( cy, cx, 'f' );
                }

                syncPoint.unlock();
            }
        }

        syncPoint.lock();

        Field& mField = minesweeper.getField();

        for ( int i = 0; i < fieldSize.first; ++i )
        {
            for ( int j = 0; j < fieldSize.second; ++j )
            {
                if ( mField.isOpened( i, j ) )
                {
                    if ( mField.isBomb( i, j ) )
                    {
                        if ( minesweeper.isGameOver() )
                            gameField.field[i][j].currentState = "b";
                        else
                           gameField.field[i][j].currentState = "h";
                    }
                    else
                       gameField.field[i][j].currentState = to_string( mField.getValue( i, j ) );
                }
                else
                {
                    if ( mField.isFlag( i, j ) )
                       gameField.field[i][j].currentState = "f";
                    else
                       gameField.field[i][j].currentState = "h";
                }
            }
        }

        quit = quitLocal;
        mainDrawer->draw();

        syncPoint.unlock();

        SDL_Delay( 1 );
    }

    syncPoint.lock();
    cout << "Minesweeper io thread done" << endl;
    syncPoint.unlock();
}
