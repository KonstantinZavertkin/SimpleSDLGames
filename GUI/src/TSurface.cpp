#include "TSurface.h"

namespace io_submodule
{
    TSurface::TSurface()
    {
    };

    TSurface::TSurface( SDL_Surface* newSurface )
    {
        surfacePtr = newSurface;
    };

    TSurface::TSurface( const std::string pathToBmp )
    {
        surfacePtr = SDL_LoadBMP( pathToBmp.c_str() );

        if ( surfacePtr == nullptr )
        {
            std::string errorMsg = std::string( "Can't load BMP, path: " );
            errorMsg += pathToBmp + std::string( ", error:" ) + SDL_GetError();

            throw std::runtime_error( errorMsg );
        }
    };

    TSurface::~TSurface()
    {
        if ( surfacePtr == nullptr )
            SDL_FreeSurface( surfacePtr );
    }

    TSurface::TSurface( TSurface&& oldVar ) noexcept
    {
        surfacePtr = oldVar.surfacePtr;
        oldVar.surfacePtr = nullptr;
    }

    TSurface& TSurface::operator=( TSurface&& oldVar ) noexcept
    {
        surfacePtr = oldVar.surfacePtr;
        oldVar.surfacePtr = nullptr;
        return *this;
    };

    SDL_Surface* TSurface::getSurface()
    {
        return surfacePtr;
    }

    int TSurface::getSurfaceWidth() const
    {
        if ( surfacePtr )
           return surfacePtr->w;

        return 0;
    };
};
