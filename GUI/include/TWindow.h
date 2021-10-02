#ifndef _TWINDOW_H_
#define _TWINDOW_H_

#include <string>
#include <exception>
#include <iostream>
#include "sdl2_include.h"
#include "TParams.h"

namespace io_submodule
{
    class TWindow
    {
        public:
            TWindow( const std::string windowName, const TRectangleDescription rectStruct );
            ~TWindow();

            SDL_Window* getWindow();

        private:
            SDL_Window* windowPtr = nullptr;

            TWindow( const TWindow& ) = delete;
            TWindow& operator=( const TWindow& ) = delete;
    };
};

#endif // _TWINDOW_H_
