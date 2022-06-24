#include "TTetrisBackend.h"

#include <algorithm>
#include <iostream>

namespace game_backend
{
    TTetrisBackend::TTetrisBackend( TCoords fieldSize )
        : gameField( fieldSize.first, fieldSize.second ), nextFigureField( 4, 4 ), fieldSize( fieldSize )
    {
    }

    TTetrisBackend::~TTetrisBackend()
    {
    }

    std::optional<size_t> TTetrisBackend::checkFullLines() const
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
    }

    void TTetrisBackend::createFigure()
    {
        TCoords startPos = {1, 0};
        TCoords rotationPoint = {1, 5};
        vector<TCoords> figurePoints = {};
        auto figureColor = TCellStates::blueColorStateKey;

        TCellsBlock block( gameField );
        TCellsBlock nextBlock( nextFigureField );

        currentFigureId = nextFigureId;
        nextFigureId = rand() % 7;

        auto mapIdToFigure = [&figurePoints, &figureColor, &rotationPoint, &startPos]( size_t figureIdVar )
        {
            if ( figureIdVar == 0 )
            {
                figurePoints = { {0, 0}, {0, 1}, {0, 2}, {1, 1} };
                figureColor = TCellStates::blueColorStateKey;
            }
                
            if ( figureIdVar == 1 )
            {
                figurePoints = { {0, 0}, {0, 1}, {0, 2}, {0, 3} };
                figureColor = TCellStates::greenColorStateKey;
                rotationPoint = {0, 5};
            }

            if ( figureIdVar == 2 )
            {
                figurePoints = { {0, 0}, {0, 1}, {0, 2}, {1, 0} };
                figureColor = TCellStates::redColorStateKey;
            }

            if ( figureIdVar == 3 )
            {
                figurePoints = { {0, 0}, {1, 0}, {1, 1}, {1, 2} };
                figureColor = TCellStates::cyanColorStateKey;
            }

            if ( figureIdVar == 4 )
            {
                figurePoints = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };
                figureColor = TCellStates::magentaColorStateKey;
                startPos = {1, 1};
            }

            if ( figureIdVar == 5 )
            {
                figurePoints = { {0, 0}, {0, 1}, {1, 1}, {1, 2} };
                figureColor = TCellStates::yellowColorStateKey;
            }

            if ( figureIdVar == 6 )
            {
                figurePoints = { {0, 1}, {0, 2}, {1, 0}, {1, 1} };
                figureColor = TCellStates::orangeColorStateKey;
            }
        };

        mapIdToFigure( nextFigureId );

        nextBlock.gameField.resetField();

        nextBlock.initFigure( startPos, figurePoints, figureColor, figureId );
        nextBlock.setRotatePoint( rotationPoint );

        mapIdToFigure( currentFigureId );

        startPos = {0, 4};
        block.initFigure( startPos, figurePoints, figureColor, ++figureId );
        block.setRotatePoint( rotationPoint );

        allBlocks.push_back( block );

        if ( block.isGameOver() )
        {
            quit = true;
            gameOver = true;
        }
    }

    void TTetrisBackend::createFigureIfRequired()
    {
        if ( allBlocks.empty() )
            createFigure();

        if ( !allBlocks.empty() )
        {
            if ( !allBlocks.back().canMove )
                createFigure();
        }

        showBlockShadow();
    }

    void TTetrisBackend::showBlockShadow()
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
    }

    void TTetrisBackend::gameStep()
    {
        if ( !pauseGame )
        {
            createFigureIfRequired();

            const auto maybeFullLines = checkFullLines();

            if ( maybeFullLines )
            {
                gameField.scrollField( {1, 0}, maybeFullLines );
                
                currentTimeToSleep = scrollTimeToSleep;
                ++gameScoreDelta;
            }
            else
            {
                currentTimeToSleep = realTimeToSleep;

                if ( !allBlocks.empty() )
                {
                    allBlocks.back().step();

                    if ( gameScoreDelta )
                    {
                        if ( gameScoreDelta > 1 )
                            gameScoreDelta = 1 << gameScoreDelta;

                        gameScore += gameScoreDelta;
                        gameScoreDelta = 0;
                        ++figuresCounter;
                    }
                }
            }
        }
    }

    size_t TTetrisBackend::getTimeToSleep()
    {
        size_t valToReturn = currentTimeToSleep;

        if ( isAccelerate )
        {
            if ( prevFiguresCounter != figuresCounter )
            {
                realTimeToSleep -= 10;
                realTimeToSleep = max( 0, static_cast<int>( realTimeToSleep ) );
                prevFiguresCounter = figuresCounter;
            }

            currentTimeToSleep = realTimeToSleep;
        }

        return valToReturn;
    }

    void TTetrisBackend::reset()
    {
        allBlocks = {};
        virtualBlock = {};
        figureId = 0;
        currentFigureId = 0;
        nextFigureId = 0;
        pauseGame = false;
        quit = false;
        gameOver = false;

        gameScore = 0;
        isAccelerate = true;
        gameScoreDelta = 0;
        realTimeToSleep = mainTimeToSleep;
        currentTimeToSleep = mainTimeToSleep;
        figuresCounter = 0;
        prevFiguresCounter = 0;

        gameField = TGameField( fieldSize.first, fieldSize.second );
        nextFigureField = TGameField( 4, 4 );
    }
}
