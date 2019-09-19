#include "TCellRectangles.h"

namespace io_submodule
{
    TCellRectangles::TCellRectangles()
    {
    };

    TCellRectangles::~TCellRectangles()
    {
    };

    void TCellRectangles::setCellsFieldParams( TRectangleDescription mainFieldParams, TCellsFieldParams gameCellsParams )
    {
        this->gameFieldSize = mainFieldParams;
        this->gameCellsParams = gameCellsParams;
    };

    void TCellRectangles::calcGrid()
    {
        cellsMap = vector<vector<TRectangleDescription>>( gameCellsParams.xCellsCount );

        for ( auto& cellLine : cellsMap )
            cellLine = vector<TRectangleDescription>( gameCellsParams.yCellsCount );

        TRectangleDescription cell;
        cell.height = gameCellsParams.cellHeight;
        cell.width = gameCellsParams.cellWidth;

        for ( size_t i = 0; i < cellsMap.size(); ++i )
        {
            for ( size_t j = 0; j < cellsMap[i].size(); ++j )
            {
                cell.xStart = j * cell.width + gameFieldSize.xStart;
                cell.yStart = i * cell.height + gameFieldSize.yStart;
                cellsMap[i][j] = cell;
            }
        }
    };

    TRectangleDescription TCellRectangles::getCellRectangle( const size_t x, const size_t y ) const
    {
        return cellsMap[x][y];
    };
};
