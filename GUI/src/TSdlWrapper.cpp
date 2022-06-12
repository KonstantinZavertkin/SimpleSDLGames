#include "TSdlWrapper.h"
#include <iostream>
#include <exception>

namespace io_submodule
{
    TSdlWrapper* TSdlWrapper::instance = nullptr;

    TSdlWrapper* TSdlWrapper::getInstance()
    {
        if ( !instance )
            return instance = new TSdlWrapper();;

        return instance;
    };

    void TSdlWrapper::deteteInstance()
    {
        if ( instance )
            delete instance;

        instance = nullptr;
    };

    TSdlWrapper::TSdlWrapper()
    {
        std::cout << "SDL subsystem initialization...";

        if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
        {
            std::string errorMessage = "Can't init SDL subsystem";
            throw std::runtime_error( errorMessage.c_str() );
        };
        
        std::cout << "Done" << std::endl;
    };
    
    TSdlWrapper::~TSdlWrapper()
    {
        std::cout << "SDL subsystem shut down...";

        SDL_Quit();
        
        std::cout << "Done" << std::endl;
    };
};
