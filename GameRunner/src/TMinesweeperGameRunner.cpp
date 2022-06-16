#include <thread>

#include "TMinesweeperGameRunner.h"
#include "TMinesweeperGame.h"
#include "TFieldDrawer.h"

using namespace std;

TMinesweeperGameRunner::TMinesweeperGameRunner( TRenderer& rendererRef )
    : renderer( rendererRef )
{
}

void TMinesweeperGameRunner::init()
{
    cellsFieldParams.xCellsCount = 20;
    cellsFieldParams.yCellsCount = 20;
    cellsFieldParams.cellHeight = 16;
    cellsFieldParams.cellWidth = 16;
}

void TMinesweeperGameRunner::run()
{
    TCellRectangles mainFieldCellsGrid;
    mainFieldCellsGrid.setCellsFieldParams( activeGameField, cellsFieldParams );
    mainFieldCellsGrid.calcGrid();

    TMinesweeperGame game( { cellsFieldParams.yCellsCount, cellsFieldParams.xCellsCount } );

    TSurface surface0 = TSurface( "minesweeper_sprites.bmp" );
    TTexture texture0 = TTexture( renderer, surface0 );
    texture0.setTexturePart( { 0, 0 }, { 16, 16 } );

    TSurface surface1 = TSurface( "minesweeper_sprites.bmp" );
    TTexture texture1 = TTexture( renderer, surface1 );
    texture1.setTexturePart( { 16, 0 }, { 16, 16 } );
    texture1.setStartPoint( { 30, 30 } );
    texture1.setScalingFactor( 2 );

    vector<TSurface> surfaces;
    vector<TTexture> textures;

    for ( size_t i = 0; i < 16; ++i )
    {
        surfaces.emplace_back( "minesweeper_sprites.bmp" );
        textures.emplace_back( renderer );
    }

    for ( size_t i = 0; i < 16; ++i )
    {
        textures[i].updateSurface( surfaces[i] );
        textures[i].setTexturePart( { i * 16, 0 }, { 16, 16 } );
        textures[i].setStartPoint( { i * 20 + 60, 500 } );
    }
    

    //TGameField gameField;

    TTexturesFieldDrawer fieldDrawer( game.gameField, renderer, mainFieldCellsGrid );
    fieldDrawer.textures = &textures;
    fieldDrawer.textureSliceSize = { 16, 16 };

    fieldDrawer.cellsMapper = []( const TCell& )
    {
        return 0;
    };

    TDrawer mainDrawer( renderer );
    //mainDrawer.addPrimitive( background );
    mainDrawer.addTexture( &texture0 );
    mainDrawer.addTexture( &texture1 );
    mainDrawer.addField( &fieldDrawer );

    for ( size_t i = 0; i < 16; ++i )
    {
        mainDrawer.addTexture( &textures[i] );
    }

    game.mainDrawer = &mainDrawer;

    thread mainThr1( &TMinesweeperGame::gameThread, &game );

    game.ioThread();

    mainThr1.join();
}
