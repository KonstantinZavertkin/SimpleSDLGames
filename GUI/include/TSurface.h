#ifndef _TSURFACE_H_
#define _TSURFACE_H_

#include <iostream>
#include <string>
#include <SDL2/SDL.h>

namespace io_submodule
{
    class TSurface
    {
        public:
            TSurface( const std::string pathToBmp );
            ~TSurface();

            SDL_Surface* getSurface();

        private:
            SDL_Surface* surfacePtr = nullptr;

            TSurface( const TSurface& ) = delete;
            TSurface& operator=(const TSurface& ) = delete;

    };
};

#endif // _TSURFACE_H_
