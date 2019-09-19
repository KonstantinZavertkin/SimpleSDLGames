#include "TSurface.h"

namespace io_submodule
{
    TSurface::TSurface( const std::string pathToBmp )
    {
        surfacePtr = SDL_LoadBMP( pathToBmp.c_str() );

        if ( surfacePtr == nullptr )
        {
            std::string errorMsg = std::string( "Can't load BMP, path: " );
            errorMsg += pathToBmp+ std::string( ", error:" ) + SDL_GetError();

            throw std::runtime_error( errorMsg );
        }
    };

    TSurface::~TSurface()
    {
        if ( surfacePtr == nullptr )
            SDL_FreeSurface( surfacePtr );
    };

    SDL_Surface* TSurface::getSurface()
    {
        return surfacePtr;
    };
};
