#include "TDrawer.h"

namespace io_submodule
{
    TDrawer::TDrawer( TRenderer& renderer ) : rendererRef( renderer )
    {};

    TDrawer::~TDrawer()
    {};

    void TDrawer::draw( TTexture& texture )
    {
        SDL_RenderClear( rendererRef.getRenderer() );
        SDL_RenderCopy( rendererRef.getRenderer(), texture.getTexturePtr(), nullptr, nullptr );
    }

    void TDrawer::draw( TTexture& texture, std::pair<int, int> point )
    {
        SDL_Rect r;
        r.x = point.first;
        r.y = point.second;
        r.h = texture.getSurface().getSurface()->h;
        r.w = texture.getSurface().getSurface()->w;

        TColorRGB color = { 0, 0, 0, 0xFF };

        SDL_SetRenderDrawColor( rendererRef.getRenderer(), color.r, color.g, color.b, color.alpha );
        SDL_RenderFillRect( rendererRef.getRenderer(), &r );
        SDL_RenderCopy( rendererRef.getRenderer(), texture.getTexturePtr(), nullptr, &r );
    };

    void TDrawer::draw( TRectangleDescription rectangleParams )
    {
        SDL_Rect tempRect;
        tempRect.x = rectangleParams.xStart;
        tempRect.y = rectangleParams.yStart;
        tempRect.h = rectangleParams.height;
        tempRect.w = rectangleParams.width;
        const TColorRGB& color = rectangleParams.color;

        SDL_SetRenderDrawColor( rendererRef.getRenderer(), color.r, color.g, color.b, color.alpha );

        if ( rectangleParams.isFilled )
            SDL_RenderFillRect( rendererRef.getRenderer(), &tempRect );
        else
            SDL_RenderDrawRect( rendererRef.getRenderer(), &tempRect );
    };

    void TDrawer::updateScreen()
    {
        SDL_Delay( 1 );
        SDL_RenderPresent( rendererRef.getRenderer() );
    }

    TRenderer& TDrawer::getRenderer()
    {
        return rendererRef;
    };
};
