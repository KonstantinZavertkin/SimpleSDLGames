#include "sdl2_include.h"
#include "TSnakeGame.h"
#include <iostream>

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
            if ( cell.currentState == game_backend::TCellStates::eatStateKey )
                isRequiredFood = false;
    }

    if ( isRequiredFood )
    {
        auto x = rand() % gameField.field.size();
        auto y = rand() % gameField.field[0].size();
        gameField.field[x][y].currentState = game_backend::TCellStates::eatStateKey;
    }
};

void TSnakeGame::gameThread()
{
    bool quit = false;

    while ( !quit )
    {
        quit = step();

        if ( quit )
            cout << "Game over, score: " << snake.snakeCells.size() << endl;

        fDrawer->draw();
        SDL_Delay( 100 );
    }
};

void TSnakeGame::ioThread()
{
    SDL_Event exitEvent;
    bool quit = false;

    while ( !quit )
    {
        while ( SDL_PollEvent( &exitEvent ) != 0 )
        {
            if ( exitEvent.type == SDL_QUIT )
                quit = true;

            if ( exitEvent.type == SDL_KEYDOWN )
            {
                auto keyValue = exitEvent.key.keysym.sym;

                if ( keyValue == SDLK_UP || keyValue == SDLK_w )
                    turn( { -1, 0 } );
                    
                if ( keyValue == SDLK_DOWN || keyValue == SDLK_s )
                    turn( { 1, 0 } );

                if ( keyValue == SDLK_LEFT || keyValue == SDLK_a )
                    turn( { 0, -1 } );

                if ( keyValue == SDLK_RIGHT || keyValue == SDLK_d )
                    turn( { 0, 1 } );
            }
        }

        SDL_Delay( 1 );
    }
};
