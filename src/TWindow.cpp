#include "TWindow.h"

namespace io_submodule
{
    TWindow::TWindow( const std::string name, const TRectangleDescription rectStruct  )
    {
        auto x = rectStruct.xStart;
        auto y = rectStruct.yStart;
        auto w = rectStruct.width;
        auto h = rectStruct.height;

        windowPtr = SDL_CreateWindow( "Main window", x, y, w, h, SDL_WINDOW_SHOWN );

        if ( windowPtr == nullptr )
        {
            std::string errorMessage = std::string( "SDL error (mainWindow): ") + std::string( SDL_GetError() );
            throw std::runtime_error( errorMessage );
        }
    };

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
