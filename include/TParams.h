#ifndef _TPARAMS_H_
#define _TPARAMS_H_

#include <cstddef>

namespace io_submodule
{
    //!< Color description
    //!< Default is white
    struct TColorRGB
    {
        unsigned int r = 0xFF;
        unsigned int g = 0xFF;
        unsigned int b = 0xFF;
        unsigned int alpha = 0xFF;
    };

    struct TRectangleDescription
    {
        size_t xStart = 0;
        size_t yStart = 0;
        size_t width = 0;
        size_t height = 0;
        TColorRGB color;
        bool isFilled = false;
    };

    struct TCellsFieldParams
    {
        size_t xCellsCount = 0;
        size_t yCellsCount = 0;
        size_t cellWidth = 0;
        size_t cellHeight = 0;
    };
};

#endif
