#ifndef _TSCORESTOREGE_H_
#define _TSCORESTOREGE_H_

#include <string>


class TScoreStorage
{
    public:
        TScoreStorage( const std::string& path );

        void setScore( unsigned score );
        unsigned getScore();

    private:
        std::string path;
};

#endif

