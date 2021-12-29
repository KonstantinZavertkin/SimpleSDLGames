#include "TFontDrawer.h"

TFontDrawer::TFontDrawer( TFontTTF& fontRendererRef ) : fontRenderer( fontRendererRef )
{
}

TFontDrawer::~TFontDrawer()
{
}

void TFontDrawer::setText( const string& textToPrint )
{
    fontRenderer.setText( textToPrint );
}
