#include "TFontDrawer.h"

TFontDrawer::TFontDrawer( TRenderer& renderer, const string pathToTtf, const size_t fontSize )
    : fontRenderer( renderer, pathToTtf, fontSize )
{
}

TFontDrawer::~TFontDrawer()
{
}

void TFontDrawer::setText( const string& textToPrint )
{
    fontRenderer.setText( textToPrint );
}

void TFontDrawer::drawText()
{
    fontRenderer.drawText();
}

TFontTTF& TFontDrawer::getFontDrawerRef()
{
    return fontRenderer;
}
