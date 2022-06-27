#include "TStepAction.h"
#include "TMinesweeperField.h"
namespace game_backend
{
    void TStepAction::initialStepAction( int sizeX, int sizeY )
    {
        this->sizeX = sizeX;
        this->sizeY = sizeY;
    };

    Field& TStepAction::getField()
    {
        return field;
    };

    void TStepAction::changeFlag( int x, int y )
    {
        field.changeFlag( x, y );
    };

    int TStepAction::getAmountOfFlagsInSquare( int x, int y )
    {
        int localAmountOfType = 0;

        for( int j = ( y - 1 ); j <= ( y + 1 ); ++j )
        {
            for( int i = ( x - 1 ); i <= ( x + 1 ); ++i )
            {
                if( ( i >= 0 ) && ( i < sizeX ) && ( j >= 0 ) && ( j < sizeY ) )
                {
                    if( field.isFlag( i, j ) )
                    {
                        localAmountOfType++;
                    }
                }
            }
        }

        return localAmountOfType;
    };

    void TStepAction::tryOpen( int x, int y )
    {
        if( field.isFlag( x, y ) )
        {
            field.changeFlag( x, y );
        }
        else
        {
            if( field.isOpened( x, y ) )
            {
                if( field.getValue( x, y ) == getAmountOfFlagsInSquare( x, y ) )
                {
                    openCells( x, y );
                }
            }
            else
            {
                openCells( x, y );
            }
        }
    }

    void TStepAction::openCells( int x, int y )
    {
        field.setOpened( x, y );

        const auto bombsAround = field.getValue( x, y );

        if( bombsAround == 0 )
        {
            for( int j = ( y - 1 ); j <= ( y + 1 ); ++j )
            {
                for( int i = ( x - 1 ); i <= ( x + 1 ); ++i )
                {
                    if( ( i >= 0 ) && ( i < sizeX ) && ( j >= 0 ) && ( j < sizeY ) )
                    {
                        if( !( ( i == x ) && ( j == y ) ) )
                        {
                            if( !field.isOpened( i, j ) && !field.isFlag( i, j ) && !field.isBomb( i, j ) )
                            {
                                field.setOpened( i, j );

                                if( field.getValue( i, j ) == 0 )
                                {
                                    openCells( i, j );
                                }
                            }
                        }
                    }
                }
            }
        }
        else
        {
            int flagsCount = 0;

            for( int j = ( y - 1 ); j <= ( y + 1 ); ++j )
            {
                for( int i = ( x - 1 ); i <= ( x + 1 ); ++i )
                {
                    if( ( i >= 0 ) && ( i < sizeX ) && ( j >= 0 ) && ( j < sizeY ) )
                    {
                        if ( field.isFlag( i, j) )
                        ++flagsCount;
                    }
                }
            }

            if ( bombsAround == flagsCount )
            {
                for( int j = ( y - 1 ); j <= ( y + 1 ); ++j )
                {
                    for( int i = ( x - 1 ); i <= ( x + 1 ); ++i )
                    {
                        if( ( i >= 0 ) && ( i < sizeX ) && ( j >= 0 ) && ( j < sizeY ) )
                        {
                            if( !( ( i == x ) && ( j == y ) ) )
                            {
                                if( !field.isOpened( i, j ) && !field.isFlag( i, j ) )
                                {
                                    field.setOpened( i, j );

                                    if( field.getValue( i, j ) == 0 )
                                    {
                                        openCells( i, j );
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    };

    TStepAction::TStepAction( Field& fieldArg ) : field( fieldArg )
    {
    }

    void TStepAction::performAction( int x, int y, char currentAction )
    {
        if( currentAction == 'f' )
        {
            field.changeFlag( x, y );
        }
        else
        {
            tryOpen( x, y );
        }
    };
}