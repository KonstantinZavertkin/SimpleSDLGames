#include "TFontDrawer.h"

TFontDrawer::TFontDrawer( TRenderer& renderer, const string pathToTtf, const size_t fontSize )
    : fontRenderer( renderer, pathToTtf, fontSize )
{
}

TFontDrawer::~TFontDrawer()
{
}

void TFontDrawer::setPoint( TCoords point, TTextAlignment alignment )
{
    fontRenderer.setPoint( point, alignment );
}

void TFontDrawer::setColor( const TColorRGB& colorRgb )
{
    fontRenderer.setColor( colorRgb );
}

TFontDrawer::TFontDrawer( TFontDrawer&& old ) noexcept: fontRenderer( std::move( old.fontRenderer ) )
{
    isVisible = old.isVisible;
}

TFontDrawer& TFontDrawer::operator=( TFontDrawer&& old ) noexcept
{
    fontRenderer = std::move( old.fontRenderer );
    isVisible = old.isVisible;
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
