#include <algorithm>
#include <iostream>
#include <cmath>
#include <thread>

#include "sdl2_include.h"
#include "TSnakeGame.h"
#include "CommonTypes.hpp"

TSnakeGame::TSnakeGame( TCoords fieldSize, size_t snakeLength )
    : gameBackend( fieldSize, snakeLength )
{
};

TSnakeGame::~TSnakeGame()
{
}

void TSnakeGame::runGame()
{
    thread mainThr( &TSnakeGame::gameThread, this );
    ioThread();
    mainThr.join();
};

void TSnakeGame::gameThread()
{
    bool quitLocal = false;
    gameBackend.performStep = true;

    while ( !quitLocal )
    {
        if ( !gameBackend.quitEvent )
        {
            syncPoint.lock();
            quitLocal = gameBackend.stepGame();
            syncPoint.unlock();

            SDL_Delay( gameBackend.timeDelay );
        }
        else
            quitLocal = true;
    }
};

void TSnakeGame::ioThread()
{
    gameBackend.bestScore = gameBackend.bestScoreStorage.getScore();
    gameBackend.currentScore = 0;
    SDL_Event ioEvent;
    bool pauseLocal = false;
    bool quitLocal = false;

    TCoords vectorLast = { 0, 0 };
    TCoords vectorNext = { 0, 0 };

    while ( !quitLocal )
    {
        while ( SDL_PollEvent( &ioEvent ) != 0 )
        {
            if ( ioEvent.type == SDL_QUIT )
            {
                quitLocal = true;
                syncPoint.lock();
                gameBackend.quitEvent = quitLocal;
                gameBackend.timeDelay = 0;
                syncPoint.unlock();
            }

            if ( ioEvent.type == SDL_KEYDOWN )
            {
                auto keyValue = ioEvent.key.keysym.sym;

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
                }
                else
                {
                    syncPoint.lock();

                    if ( pauseMenu->show() != 0 )
                    {
                        quitLocal = true;
                        gameBackend.quitEvent = quitLocal;
                    }

                    syncPoint.unlock();
                }
                    

                syncPoint.lock();

                gameBackend.pauseGame = pauseLocal;

                if ( !pauseLocal )
                {
                    if ( vectorNext == vectorLast )
                        gameBackend.performStep = true;
                    else
                    {
                        gameBackend.rotationsQueue.push_back( vectorNext );

                        while ( gameBackend.rotationsQueue.size() > 2 )
                            gameBackend.rotationsQueue.pop_front();

                        vectorLast = vectorNext;
                    }
                }

                syncPoint.unlock();
            }
        }

        syncPoint.lock();

        gameBackend.currentScore = gameBackend.snake.snakeCells.size() - gameBackend.initSnakeLength;
        scorePrinter->setText( "Score: " + to_string( gameBackend.currentScore ) );
        bestScorePrinter->setText( "Best: " + to_string( gameBackend.bestScore ) );

        if ( !quitLocal )
            mainDrawer->draw();

        if ( gameBackend.quitEvent )
            quitLocal = true;

        syncPoint.unlock();
        
        SDL_Delay( 1 );
    }

    if ( gameBackend.currentScore > gameBackend.bestScore )
       gameBackend.bestScoreStorage.setScore( gameBackend.currentScore );
};
