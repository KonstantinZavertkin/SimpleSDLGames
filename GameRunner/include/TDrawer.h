#ifndef _TDRAWER_H_
#define _TDRAWER_H_

#include <vector>

#include "CommonTypes.hpp"
#include "TFieldDrawer.h"
#include "TFontDrawer.h"
#include "TRenderer.h"

namespace io_submodule
{
    class TDrawer
    {
        public:
            TDrawer( TRenderer& rendererRef );
            ~TDrawer();

            void addPrimitive( TRectangleDescription primitiveDescription );
            void addField( TFieldDrawer* fieldDrawerPtr );
            void addTexture( TTexture* texturePtr );
            void addText( TFontDrawer* textPrinterPtr );
            TRenderer& getRendererRef();

            void draw();

        private:
            TRenderer& renderer;

            vector<TRectangleDescription> staticPrimitives;
            vector<TFieldDrawer*> fieldDrawers;
            vector<TTexture*> textures;
            vector<TFontDrawer*> textPrinters;
    };
};

#endif
