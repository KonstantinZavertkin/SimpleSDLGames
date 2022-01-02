#include "TDrawer.h"

namespace io_submodule
{
    TDrawer::TDrawer( TRenderer& renderer ) : rendererRef( renderer )
    {
        SDL_RenderClear( rendererRef.getRenderer() );
    };

    TDrawer::~TDrawer()
    {};

    void TDrawer::draw( TTexture& texture, std::pair<int, int> point )
    {
        SDL_Rect r;
        r.x = point.first;
        r.y = point.second;
        r.h = texture.getSurface().getSurface()->h;
        r.w = texture.getSurface().getSurface()->w;

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

        const TColorRGB colorW = { 0xFF, 0xFF, 0xFF, 0x0 };

        SDL_SetRenderDrawColor( rendererRef.getRenderer(), colorW.r, colorW.g, colorW.b, colorW.alpha );
    }

    void TDrawer::resetScreen()
    {
        SDL_RenderClear( rendererRef.getRenderer() );
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
