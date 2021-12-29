#ifndef _TSURFACE_H_
#define _TSURFACE_H_

#include <iostream>
#include <string>
#include "sdl2_include.h"

namespace io_submodule
{
    class TSurface
    {
        public:

            TSurface();
            TSurface( SDL_Surface* newSurface );
            TSurface( const std::string pathToBmp );

            TSurface( TSurface&& ) noexcept;
            TSurface& operator=( TSurface&& ) noexcept;

            ~TSurface();

            SDL_Surface* getSurface();

        private:
            SDL_Surface* surfacePtr = nullptr;

            TSurface( const TSurface& ) = delete;
            TSurface& operator=( const TSurface& ) = delete;

    };
};

#endif // _TSURFACE_H_
