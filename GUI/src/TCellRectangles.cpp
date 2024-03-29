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
        cellsMap = vector<vector<TRectangleDescription>>( gameCellsParams.yCellsCount );

        for ( auto& cellLine : cellsMap )
            cellLine = vector<TRectangleDescription>( gameCellsParams.xCellsCount );

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
    }

    std::optional<TCoords> TCellRectangles::getCellCoords( size_t x, size_t y ) const
    {
        int relativeX = ( x - gameFieldSize.xStart ) / gameCellsParams.cellWidth;
        int relativeY = ( y - gameFieldSize.yStart ) / gameCellsParams.cellHeight;

        if ( relativeX < 0 || relativeX > gameCellsParams.xCellsCount - 1 )
           return {};

        if ( relativeY < 0 || relativeY > gameCellsParams.yCellsCount - 1 )
           return {};

        return TCoords{ relativeX, relativeY };
    };
};
