#include <iostream>
#include <algorithm>
#include "TTetrisGame.h"

TTetrisGame::TTetrisGame( pair<size_t, size_t> fieldSize )
    : gameField( fieldSize.first, fieldSize.second )
{
};

TTetrisGame::~TTetrisGame()
{
}

optional<size_t> TTetrisGame::checkFullLines()
{
    optional<size_t> maybeLineIndex;

    auto isNotVoidCell = []( const TCell& cell )
    {
        return ( cell.currentState != TCellStates::backgroundStateKey ) &&
               ( cell.canBeMoved == false ) &&
               ( cell.currentState != TCellStates::virtualFigure );
    };

    for ( auto i = gameField.field.size(); i > 0; i-- )
    {
        const auto& currentLine = gameField.field[i - 1];

        if ( all_of( currentLine.begin(), currentLine.end(), isNotVoidCell ) )
        {
            maybeLineIndex = i - 1;
            break;
        }  
    }

    return maybeLineIndex;
};

void TTetrisGame::gameThread()
{
    size_t timeToSleep = 500;
    std::srand( time( 0 ) );

    while ( !quit )
    {
        syncPoint.lock();

        if ( !pauseGame )
        {
            if ( allBlocks.empty() )
                createFigure();
            
            if ( !allBlocks.empty() )
                if ( !allBlocks.back().canMove )
                    createFigure();

            showBlockShadow();

            const auto maybeFullLines = checkFullLines();

            if ( maybeFullLines )
            {
                gameField.scrollField( { 1, 0 }, maybeFullLines );
                timeToSleep = 100;
            }
            else
            {
                timeToSleep = 500;

                if ( !allBlocks.empty() )
                {
                    allBlocks.back().step();

                    if ( checkFullLines() )
                        timeToSleep = 100;
                }
            }
                

            //! TODO Сделать удаление фигур из очереди
        }
        
        syncPoint.unlock();

        SDL_Delay( timeToSleep );
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
    pair<int, int> vectorDefault = { 0, 0 };

    bool figureFallSignal = false;

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

                pauseGame = pauseLocal;

                if ( !pauseLocal )
                {
                    if ( vectorNext != vectorDefault )
                    {
                        if ( !allBlocks.empty() )
                        {
                            if ( vectorNext == vectorUp )
                            {
                                allBlocks.back().turn( {0, 0} );
                            }
                            else
                            {
                                allBlocks.back().moveDirection = vectorNext;
                                allBlocks.back().step();
                            }

                            showBlockShadow();
                        }

                        vectorNext = vectorDefault;
                    }

                    if ( figureFallSignal )
                    {
                        figureFallSignal = false;

                        while ( allBlocks.back().canMove )
                            allBlocks.back().step();
                    }
                }

                syncPoint.unlock();
            }
        }

        syncPoint.lock();
        quitLocal = quit;
        fDrawer->draw();
        syncPoint.unlock();

        SDL_Delay( 1 );
    }

    cout << "Tetris io thread done" << endl;
};

void TTetrisGame::createFigure()
{
    pair<size_t, size_t> startPos = {0, 5};
    pair<size_t, size_t> rotationPoint = {1, 6};
    vector<pair<size_t, size_t>> figurePoints = {};
    auto figureColor = TCellStates::blueColorStateKey;

    TCellsBlock block( gameField );

    size_t idLocal = rand() % 7;

    if ( idLocal == 0 )
    {
        figurePoints = { {0, 0}, {0, 1}, {0, 2}, {1, 1} };
        figureColor = TCellStates::blueColorStateKey;
    }
        
    if ( idLocal == 1 )
    {
        figurePoints = { {0, 0}, {0, 1}, {0, 2}, {0, 3} };
        figureColor = TCellStates::greenColorStateKey;
        rotationPoint = {0, 6};
    }

    if ( idLocal == 2 )
    {
        figurePoints = { {0, 0}, {0, 1}, {0, 2}, {1, 0} };
        figureColor = TCellStates::redColorStateKey;
    }

    if ( idLocal == 3 )
    {
        figurePoints = { {0, 0}, {1, 0}, {1, 1}, {1, 2} };
        figureColor = TCellStates::cyanColorStateKey;
    }

    if ( idLocal == 4 )
    {
        figurePoints = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
        figureColor = TCellStates::magentaColorStateKey;
    }

    if ( idLocal == 5 )
    {
        figurePoints = { {0, 0}, {0, 1}, {1, 1}, {1, 2} };
        figureColor = TCellStates::yellowColorStateKey;
    }

    if ( idLocal == 6 )
    {
        figurePoints = { {0, 1}, {0, 2}, {1, 0}, {1, 1} };
        figureColor = TCellStates::orangeColorStateKey;
    }

    block.initFigure( startPos, figurePoints, figureColor, ++figureId );
    block.setRotatePoint( rotationPoint );

    allBlocks.push_back( block );

    if ( block.isGameOver() )
        quit = true;
};

void TTetrisGame::showBlockShadow()
{
    if ( quit )
        return;

    virtualBlock = nullptr;
    virtualBlock = make_unique<TCellsBlock>( TCellsBlock( allBlocks.back() ) );
    virtualBlock->clearVirtual();
    virtualBlock->makeVirtual();

    while ( virtualBlock->canMove )
        virtualBlock->step();

    allBlocks.back().tryWriteFigure();
};
