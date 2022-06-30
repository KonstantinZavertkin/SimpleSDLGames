#include "TDrawer.h"


namespace io_submodule
{
    TDrawer::TDrawer( TRenderer& rendererRef ) : renderer( rendererRef )
    {
    }

    TDrawer::~TDrawer()
    {
    }

    void TDrawer::addPrimitive( TRectangleDescription primitiveDescription )
    {
        staticPrimitives.push_back( primitiveDescription );
    }

    void TDrawer::addField( TFieldDrawer* fieldDrawerPtr )
    {
        fieldDrawers.push_back( fieldDrawerPtr );
    }

    void TDrawer::addTexture(TTexture* texturePtr)
    {
        textures.push_back( texturePtr );
    }

    void TDrawer::addText( TFontDrawer* textPrinterPtr )
    {
        textPrinters.push_back( textPrinterPtr );
    }

    TRenderer& TDrawer::getRendererRef()
    {
        return renderer;
    }

    void TDrawer::draw()
    {
        renderer.resetScreen();

        for ( auto& primitive : staticPrimitives )
            renderer.draw( primitive );

        for ( auto& field : fieldDrawers )
           field->drawField();

        for ( auto& texturePtr : textures )
           renderer.draw( *texturePtr );

        for ( auto& textPrinter : textPrinters )
           textPrinter->drawText();

        renderer.updateScreen();

    }
};
