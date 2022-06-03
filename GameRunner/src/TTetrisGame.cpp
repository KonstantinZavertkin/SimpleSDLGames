#include <iostream>
#include <algorithm>
#include "TTetrisGame.h"

TTetrisGame::TTetrisGame( TCoords fieldSize )
    : tetrisBackend( fieldSize )
{
};

TTetrisGame::~TTetrisGame()
{
}

void TTetrisGame::gameThread()
{
    while ( !tetrisBackend.quit )
    {
        syncPoint.lock();

        tetrisBackend.gameStep();
        
        syncPoint.unlock();

        SDL_Delay( tetrisBackend.timeToSleep );
    }
    
    cout << "Tetris game thread done" << endl;
};

void TTetrisGame::ioThread()
{
    SDL_Event exitEvent;
    SDL_Delay( 125 );
    bool pauseLocal = false;
    bool quitLocal = false;

    TCoords vectorNext = { 0, 0 };
    TCoords vectorDefault = { 0, 0 };

    bool figureFallSignal = false;

    while ( !quitLocal )
    {
        while ( SDL_PollEvent( &exitEvent ) != 0 )
        {
            if ( exitEvent.type == SDL_QUIT )
            {
                quitLocal = true;
                syncPoint.lock();
                tetrisBackend.quit = quitLocal;
                syncPoint.unlock();
            }

            if ( exitEvent.type == SDL_KEYDOWN )
            {
                auto keyValue = exitEvent.key.keysym.sym;

                if ( keyValue != SDLK_ESCAPE )
                {
                    if ( keyValue == SDLK_UP || keyValue == SDLK_w )
                        vectorNext = vectorUp;

                    if ( keyValue == SDLK_DOWN || keyValue == SDLK_s )
                        vectorNext = vectorDown;

                    if ( keyValue == SDLK_LEFT || keyValue == SDLK_a )
                        vectorNext = vectorLeft;

                    if ( keyValue == SDLK_RIGHT || keyValue == SDLK_d )
                        vectorNext = vectorRight;

                    if ( keyValue == SDLK_SPACE )
                        figureFallSignal = true;
                }
                else
                    pauseLocal = !pauseLocal;

                syncPoint.lock();

                tetrisBackend.pauseGame = pauseLocal;

                if ( !pauseLocal )
                {
                    if ( vectorNext != vectorDefault )
                    {
                        if ( !tetrisBackend.allBlocks.empty() )
                        {
                            tetrisBackend.createFigureIfRequired();

                            if ( vectorNext == vectorUp )
                            {
                                tetrisBackend.allBlocks.back().turn( {0, 0} );
                            }
                            else
                            {
                                tetrisBackend.allBlocks.back().moveDirection = vectorNext;
                                tetrisBackend.allBlocks.back().step();
                            }

                            tetrisBackend.showBlockShadow();
                        }

                        vectorNext = vectorDefault;
                    }

                    if ( figureFallSignal )
                    {
                        figureFallSignal = false;

                        while ( tetrisBackend.allBlocks.back().canMove )
                            tetrisBackend.allBlocks.back().step();

                        tetrisBackend.createFigureIfRequired();
                    }
                }

                syncPoint.unlock();
            }
        }

        syncPoint.lock();
        quitLocal = tetrisBackend.quit;

        scorePrinter->setText( "Score: " + to_string( tetrisBackend.gameScore ) );
        
        mainDrawer->getRendererRef().resetScreen();
        mainDrawer->draw();
        mainDrawer->getRendererRef().updateScreen();

        syncPoint.unlock();

        SDL_Delay( 1 );
    }

    cout << "Tetris io thread done" << endl;
};
