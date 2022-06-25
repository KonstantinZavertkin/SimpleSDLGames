#include <algorithm>
#include <iostream>
#include <cmath>

#include "sdl2_include.h"
#include "TSnakeGame.h"
#include "CommonTypes.hpp"

TSnakeGame::TSnakeGame( TCoords fieldSize, size_t snakeLength )
    : snakeBackend( fieldSize, snakeLength )
{
};

TSnakeGame::~TSnakeGame()
{
};

void TSnakeGame::gameThread()
{
    bool quitLocal = false;
    snakeBackend.performStep = true;

    while ( !quitLocal )
    {
        if ( !snakeBackend.quitEvent )
        {
            syncPoint.lock();
            quitLocal = snakeBackend.stepGame();
            syncPoint.unlock();

            SDL_Delay( snakeBackend.timeDelay );
        }
        else
            quitLocal = true;
    }
};

void TSnakeGame::ioThread()
{
    snakeBackend.bestScore = snakeBackend.bestScoreStorage.getScore();
    snakeBackend.currentScore = 0;
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
                snakeBackend.quitEvent = quitLocal;
                snakeBackend.timeDelay = 0;
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
                        snakeBackend.quitEvent = quitLocal;
                    }

                    syncPoint.unlock();
                }
                    

                syncPoint.lock();

                snakeBackend.pauseGame = pauseLocal;

                if ( !pauseLocal )
                {
                    if ( vectorNext == vectorLast )
                        snakeBackend.performStep = true;
                    else
                    {
                        snakeBackend.rotationsQueue.push_back( vectorNext );

                        while ( snakeBackend.rotationsQueue.size() > 2 )
                            snakeBackend.rotationsQueue.pop_front();

                        vectorLast = vectorNext;
                    }
                }

                syncPoint.unlock();
            }
        }

        syncPoint.lock();

        snakeBackend.currentScore = snakeBackend.snake.snakeCells.size() - snakeBackend.initSnakeLength;
        scorePrinter->setText( "Score: " + to_string( snakeBackend.currentScore ) );
        bestScorePrinter->setText( "Best: " + to_string( snakeBackend.bestScore ) );

        if ( !quitLocal )
            mainDrawer->draw();

        if ( snakeBackend.quitEvent )
            quitLocal = true;

        syncPoint.unlock();
        
        SDL_Delay( 1 );
    }

    if ( snakeBackend.currentScore > snakeBackend.bestScore )
       snakeBackend.bestScoreStorage.setScore( snakeBackend.currentScore );
};
