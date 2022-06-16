#ifndef _TCellRectangles_H_
#define _TCellRectangles_H_

#include <optional>
#include <vector>
#include "CommonTypes.hpp"
#include "TParams.h"

using std::vector;

namespace io_submodule
{
    //! Класс для расчета параметров сетки игрового поля
    //! Поле представляет собой 2D массив ячеек
    class TCellRectangles
    {
        public:
            TCellRectangles();
            ~TCellRectangles();

            //!< Метод для установки параметров игрового поля
            //!< Принимает на вход структуры
            //!< TRectangleDescription - параметры окна игрового поля
            //!< TCellsFieldParams - параметры сетки игрового поля
            void setCellsFieldParams( TRectangleDescription, TCellsFieldParams );

            //!< Расчет сетки
            void calcGrid();

            //!< Метод возвращает параметры ячейки игрового поля 
            //!< в зависимости от координат этой ячейки в контексте сетки
            TRectangleDescription getCellRectangle( const size_t x, const size_t y ) const;

            std::optional<TCoords> getCellCoords( size_t x, size_t y ) const;

        private:
            TRectangleDescription gameFieldSize;              //!< Описание окна игрового поля
            TCellsFieldParams gameCellsParams;                //!< Описание сетки игрового поля

            vector<vector<TRectangleDescription>> cellsMap;   //!< Массив, представляющий сетку игрового поля
    };
};

#endif
