#ifndef _TCellRectangles_H_
#define _TCellRectangles_H_

#include <vector>
#include "TParams.h"
#include "TTexture.h"
#include "TDrawer.h"

using std::vector;

namespace io_submodule
{
    class TCellRectangles
    {
        public:
            TCellRectangles();
            ~TCellRectangles();

            void setCellsFieldParams( TRectangleDescription, TCellsFieldParams );

            void calcGrid();
            TRectangleDescription getCellRectangle( const size_t x, const size_t y ) const;

        private:
            TRectangleDescription gameFieldSize;
            TCellsFieldParams gameCellsParams;

            vector<vector<TRectangleDescription>> cellsMap;
    };
};

#endif
