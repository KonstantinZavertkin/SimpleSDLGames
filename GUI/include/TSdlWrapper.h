#ifndef _TSDLWRAPPER_H_
#define _TSDLWRAPPER_H_

#include <string>
#include "sdl2_include.h"

namespace io_submodule
{
  
    class TSdlWrapper
    {
        public:
            static TSdlWrapper* getInstance();
            static void deteteInstance();

        private:
            static TSdlWrapper* instance;

            TSdlWrapper();
            ~TSdlWrapper();
            TSdlWrapper( const TSdlWrapper& ) = delete;
            TSdlWrapper operator=( const TSdlWrapper& ) = delete;

            SDL_Window* mainWindow = nullptr;
            SDL_Renderer* renderer = nullptr;
    };
};

#endif // _TSDLWRAPPER_H_
