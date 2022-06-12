#include "TRenderer.h"

namespace io_submodule
{
    TRenderer::TRenderer( TWindow& window )
    {
        SDL_Window* windowPtr = window.getWindow();
        renderer = SDL_CreateRenderer( windowPtr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

        if ( renderer == nullptr )
        {
            std::string error = std::string( "Can't create drawer, error: " ) + SDL_GetError();
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
    }

    void TRenderer::draw( TTexture& texture, TCoords point )
    {
        SDL_Rect r;
        r.x = point.first;
        r.y = point.second;
        r.h = texture.getSurface().getSurface()->h;
        r.w = texture.getSurface().getSurface()->w;

        SDL_RenderCopy( renderer, texture.getTexturePtr(), nullptr, &r );
    }

    void TRenderer::draw( TRectangleDescription rectangleParams )
    {
        SDL_Rect tempRect;
        tempRect.x = rectangleParams.xStart;
        tempRect.y = rectangleParams.yStart;
        tempRect.h = rectangleParams.height;
        tempRect.w = rectangleParams.width;
        const TColorRGB& color = rectangleParams.color;

        SDL_SetRenderDrawColor( renderer, color.r, color.g, color.b, color.alpha );

        if ( rectangleParams.isFilled )
            SDL_RenderFillRect( renderer, &tempRect );
        else
            SDL_RenderDrawRect( renderer, &tempRect );

        const TColorRGB colorW = { 0xFF, 0xFF, 0xFF, 0x0 };

        SDL_SetRenderDrawColor( renderer, colorW.r, colorW.g, colorW.b, colorW.alpha );
    }

    void TRenderer::resetScreen()
    {
        SDL_RenderClear( renderer );
    }

    void TRenderer::updateScreen()
    {
        SDL_Delay( 1 );
        SDL_RenderPresent( renderer );
    };
};
