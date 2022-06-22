#include "TWindow.h"

namespace io_submodule
{
    TWindow::TWindow( const std::string name, const TRectangleDescription rectStruct )
    {
        auto w = rectStruct.width;
        auto h = rectStruct.height;

        windowPtr = SDL_CreateWindow( name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h, SDL_WINDOW_SHOWN );

        if ( windowPtr == nullptr )
        {
            std::string errorMessage = std::string( "SDL error (mainWindow): ") + std::string( SDL_GetError() );
            throw std::runtime_error( errorMessage );
        }
    }

    TWindow::~TWindow()
    {
        if ( windowPtr != nullptr )
            SDL_DestroyWindow( windowPtr );
    };

    SDL_Window* TWindow::getWindow()
    {
        return windowPtr;
    };
};
