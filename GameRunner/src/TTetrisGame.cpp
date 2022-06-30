#include <iostream>
#include <algorithm>
#include <thread>
#include "TTetrisGame.h"

TTetrisGame::TTetrisGame( TCoords fieldSize )
    : gameBackend( fieldSize ), bestScoreStorage( pathToBestScoreFile )
{
};

TTetrisGame::~TTetrisGame()
{
}

void TTetrisGame::initGame()
{
}

void TTetrisGame::runGame()
{
    thread mainThr( &TTetrisGame::gameThread, this );
    ioThread();
    mainThr.join();
}

void TTetrisGame::gameThread()
{
    while ( !gameBackend.quit )
    {
        syncPoint.lock();
        gameBackend.gameStep();
        syncPoint.unlock();

        SDL_Delay( gameBackend.getTimeToSleep() );
    }
};

void TTetrisGame::ioThread()
{
    bestScore = bestScoreStorage.getScore();

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
                gameBackend.quit = quitLocal;
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
                {
                    syncPoint.lock();

                    if ( pauseMenu->show() != 0 )
                    {
                        quitLocal = true;
                        gameBackend.quit = quitLocal;
                    }

                    syncPoint.unlock();
                }

                syncPoint.lock();

                gameBackend.pauseGame = pauseLocal;

                if ( !pauseLocal )
                {
                    if ( vectorNext != vectorDefault )
                    {
                        if ( !gameBackend.allBlocks.empty() )
                        {
                            gameBackend.createFigureIfRequired();

                            if ( vectorNext == vectorUp )
                            {
                                gameBackend.allBlocks.back().turn( { 0, 0 } );
                            }
                            else
                            {
                                gameBackend.allBlocks.back().moveDirection = vectorNext;
                                gameBackend.allBlocks.back().step();
                            }

                            gameBackend.showBlockShadow();
                        }

                        vectorNext = vectorDefault;
                    }

                    if ( figureFallSignal )
                    {
                        figureFallSignal = false;

                        while ( gameBackend.allBlocks.back().canMove )
                            gameBackend.allBlocks.back().step();

                        gameBackend.createFigureIfRequired();
                    }
                }

                syncPoint.unlock();
            }
        }

        syncPoint.lock();

        quitLocal = gameBackend.quit;
        currentScore = gameBackend.gameScore;
        scorePrinter->setText( "Score: " + to_string( currentScore ) );
        bestScorePrinter->setText( "Best: " + to_string( bestScore ) );

        if ( !quitLocal )
            mainDrawer->draw();

        if ( currentScore > bestScore )
           bestScoreStorage.setScore( currentScore );

        syncPoint.unlock();

        SDL_Delay( 1 );
    }
};
