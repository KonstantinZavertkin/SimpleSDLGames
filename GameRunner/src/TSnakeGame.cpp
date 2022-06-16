#include <algorithm>
#include <iostream>
#include <cmath>

#include "sdl2_include.h"
#include "TSnakeGame.h"
#include "CommonTypes.hpp"

TSnakeGame::TSnakeGame( TCoords fieldSize, size_t snakeLength )
    : gameField( fieldSize.first, fieldSize.second ), snake( gameField )
{
    initSnakeLength = snakeLength;
    snake.initCellsChain({1, 1}, initSnakeLength);
};

TSnakeGame::~TSnakeGame()
{
};

bool TSnakeGame::step()
{
    snake.step();
    checkFood();
    return snake.isGameOver();
};

void TSnakeGame::turn( TCoords rotateVector )
{
    snake.turn( rotateVector );
};

void TSnakeGame::checkFood()
{
    // Is required?
    bool isRequiredFood = true;

    for ( auto line : gameField.field )
    {
        for ( auto cell : line )
            if ( cell.currentState == TCellStates::eatStateKey )
                isRequiredFood = false;
    }

    if ( isRequiredFood )
    {
        auto x = rand() % gameField.field.size();
        auto y = rand() % gameField.field[0].size();
        gameField.field[x][y].currentState = TCellStates::eatStateKey;
    }
};

void TSnakeGame::gameThread()
{
    bool quitLocal = false;
    performStep = true;

    while ( !quitLocal )
    {
        syncPoint.lock();

        if ( ( clockCounter % 4 ) == 0 )
            performStep = true;

        if ( performStep )
        {
            if ( !rotationsQueue.empty() )
            {
                turn( rotationsQueue.front() );
                rotationsQueue.pop_front();
            }

            if ( !pauseGame )
                quitLocal = step();

            performStep = false;
        }

        if ( quitLocal )
            quit = quitLocal;
        
        if ( quit )
        {
            quitLocal = quit;
            cout << "Game over, score: " << snake.snakeCells.size() << endl;
        }

        syncPoint.unlock();

        SDL_Delay( max( 0, 50 - static_cast<int>( snake.snakeCells.size() * 2 ) ) );

        clockCounter++;
    }

    cout << "gameThread done" << endl;
};

void TSnakeGame::ioThread()
{
    SDL_Event exitEvent;
    bool pauseLocal = false;
    bool quitLocal = false;

    TCoords vectorLast = { 0, 0 };
    TCoords vectorNext = { 0, 0 };

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

        scorePrinter->setText( "Score: " + to_string( snake.snakeCells.size() - initSnakeLength ) );

        mainDrawer->getRendererRef().resetScreen();
        mainDrawer->draw();
        mainDrawer->getRendererRef().updateScreen();

        if ( quit )
            quitLocal = quit;

        syncPoint.unlock();
        
        SDL_Delay( 1 );
    }

    cout << "ioThread done" << endl;
};
