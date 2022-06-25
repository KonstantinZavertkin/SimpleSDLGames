#include <fstream>
#include "TScoreStorage.h"

TScoreStorage::TScoreStorage( const std::string& path )
{
    this->path = path;
}

void TScoreStorage::setScore( unsigned score  )
{
    std::ofstream outputFile( path );

    if ( outputFile.is_open() )
    {
        outputFile << std::to_string( score );
        outputFile.close();
    }
}

unsigned TScoreStorage::getScore()
{
    unsigned result = 0;
    std::ifstream inputFile( path );

    if ( inputFile.is_open() )
    {
        if ( !inputFile.eof() )
            inputFile >> result;

        inputFile.close();
    }

    return result;
}
