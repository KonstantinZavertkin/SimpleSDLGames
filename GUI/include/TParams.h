#ifndef _TPARAMS_H_
#define _TPARAMS_H_

#include <cstddef>

namespace io_submodule
{
    //! RGB цвет
    //! Белый по умолчанию
    struct TColorRGB
    {
        unsigned int r = 0xFF;
        unsigned int g = 0xFF;
        unsigned int b = 0xFF;
        unsigned int alpha = 0xFF;
    };

    //! Описание произвольной прямоугольной области
    struct TRectangleDescription
    {
        size_t xStart = 0;       //!< Смещение области по x
        size_t yStart = 0;       //!< Смещение области по y
        size_t width = 0;        //!< Ширина области
        size_t height = 0;       //!< Высота области
        TColorRGB color;         //!< Структура, описывающая цвет
        bool isFilled = false;   //!< Флаг заливки области
    };

    //! Описание игрового поля
    struct TCellsFieldParams
    {
        size_t xCellsCount = 0;   //!< Количество ячеек по оси x
        size_t yCellsCount = 0;   //!< Количество ячеек по оси y
        size_t cellWidth = 0;     //!< Ширина ячейки
        size_t cellHeight = 0;    //!< Высота ячейки
    };
};

#endif
