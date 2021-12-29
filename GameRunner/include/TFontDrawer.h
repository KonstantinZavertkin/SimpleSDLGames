#ifndef _TFONTDRAWER_CPP_
#define _TFONTDRAWER_CPP_

#include "TFontTTF.h"

using namespace io_submodule;

class TFontDrawer
{
    public:
        TFontDrawer( TFontTTF& fontRenderer );
        ~TFontDrawer();

        void setText( const string& textToPrint );

    private:

        TFontTTF& fontRenderer;
};


#endif
