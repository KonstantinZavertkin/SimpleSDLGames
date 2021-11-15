#include "sdl2_include.h"
#include "TSnakeGame.h"

#include <algorithm>
#include <iostream>
#include <cmath>

TSnakeGame::TSnakeGame( pair<size_t, size_t> fieldSize, size_t snakeLength ) 
    : gameField( fieldSize.first, fieldSize.second ), snake( gameField )
{
    snake.initCellsChain( { 1, 1 }, snakeLength );
};

TSnakeGame::~TSnakeGame()
{
};

bool TSnakeGame::step()
{
    cout << "step" << endl;
    snake.step();
    checkFood();
    return snake.isGameOver();
};

void TSnakeGame::turn( pair<int, int> rotateVector )
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

        fDrawer->draw();

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

        if ( quit )
        {
            quitLocal = quit;
            cout << "global quit received" << endl;
        }

        syncPoint.unlock();
        
        SDL_Delay( 1 );
    }

    cout << "ioThread done" << endl;
};
