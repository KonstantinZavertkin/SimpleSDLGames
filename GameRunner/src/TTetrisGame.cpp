#include <iostream>
#include "TTetrisGame.h"

TTetrisGame::TTetrisGame( pair<size_t, size_t> fieldSize )
    : gameField( fieldSize.first, fieldSize.second ), someBlock( gameField )
{
    vector<pair<size_t, size_t>> v { {0, 0}, {0, 1}, {0, 2}, {1, 1} };
    someBlock.initFigure( {0, 5}, v, TCellStates::blueColorStateKey );
};

TTetrisGame::~TTetrisGame()
{

};

void TTetrisGame::gameThread()
{
    bool quitLocal = false;

    while ( !quit )
    {
        syncPoint.lock();
        someBlock.step();
        syncPoint.unlock();

        SDL_Delay( 250 );
    }
    
    cout << "Tetris game thread done" << endl;
};

void TTetrisGame::ioThread()
{
    SDL_Event exitEvent;
    SDL_Delay( 125 );
    bool pauseLocal = false;
    bool quitLocal = false;

    pair<int, int> vectorUp = { -1, 0 };
    pair<int, int> vectorDown = { 1, 0 };
    pair<int, int> vectorLeft = { 0, -1 };
    pair<int, int> vectorRight = { 0, 1 };
    pair<int, int> vectorLast = { 0, 0 };
    pair<int, int> vectorNext = { 0, 0 };

    while ( !quitLocal )
    {
        while ( SDL_PollEvent( &exitEvent ) != 0 )
        {
            if ( exitEvent.type == SDL_QUIT )
            {
                quitLocal = true;
                syncPoint.lock();
                quit = quitLocal;
                syncPoint.unlock();
            }

            if ( exitEvent.type == SDL_KEYDOWN )
            {
                auto keyValue = exitEvent.key.keysym.sym;

                if ( keyValue != SDLK_SPACE )
                {
                    if ( keyValue == SDLK_UP || keyValue == SDLK_w )
                        vectorNext = vectorUp;

                    if ( keyValue == SDLK_DOWN || keyValue == SDLK_s )
                        vectorNext = vectorDown;

                    if ( keyValue == SDLK_LEFT || keyValue == SDLK_a )
                        vectorNext = vectorLeft;

                    if ( keyValue == SDLK_RIGHT || keyValue == SDLK_d )
                        vectorNext = vectorRight;
                }
                else
                    pauseLocal = !pauseLocal;

                syncPoint.lock();

                pauseGame = pauseLocal;

                if ( !pauseLocal )
                {
                    if ( vectorNext == vectorLast )
                        performStep = true;
                    else
                    {
                        rotationsQueue.push_back( vectorNext );

                        while ( rotationsQueue.size() > 2 )
                            rotationsQueue.pop_front();

                        vectorLast = vectorNext;
                    }
                }

                syncPoint.unlock();
            }
        }

        syncPoint.lock();
        fDrawer->draw();
        syncPoint.unlock();

        SDL_Delay( 250 );
    }

    cout << "Tetris io thread done" << endl;
};
