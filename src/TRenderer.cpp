  #include "TRenderer.h"

namespace io_submodule
{
    TRenderer::TRenderer( TWindow& window )
    {
        SDL_Window* windowPtr = window.getWindow();
        renderer = SDL_CreateRenderer( windowPtr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

        if ( renderer == nullptr )
        {
            std::string error = std::string( "Can't create renderer, error: " ) + SDL_GetError();
            throw std::runtime_error( error );
        }
    };

    TRenderer::~TRenderer()
    {
        if ( renderer != nullptr )
            SDL_DestroyRenderer( renderer );
    };

    SDL_Renderer* TRenderer::getRenderer()
    {
        return renderer;
    };
};
