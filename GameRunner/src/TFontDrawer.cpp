#include "TFontDrawer.h"

TFontDrawer::TFontDrawer( TRenderer& renderer, const string pathToTtf, const size_t fontSize )
    : fontRenderer( renderer, pathToTtf, fontSize )
{
}

TFontDrawer::~TFontDrawer()
{
}

TFontDrawer::TFontDrawer( TFontDrawer&& old ) noexcept: fontRenderer( std::move( old.fontRenderer ) )
{
}

TFontDrawer& TFontDrawer::operator=( TFontDrawer&& oldVal ) noexcept
{
    fontRenderer = std::move( oldVal.fontRenderer );
    return *this;
}

void TFontDrawer::setText( const string& textToPrint )
{
    fontRenderer.setText( textToPrint );
}

void TFontDrawer::drawText()
{
    if ( isVisible )
        fontRenderer.drawText();
}

TFontTTF& TFontDrawer::getFontDrawerRef()
{
    return fontRenderer;
}
