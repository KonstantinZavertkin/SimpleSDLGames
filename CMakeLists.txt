cmake_minimum_required(VERSION 3.0)

project(SnakeGame VERSION 0.1 LANGUAGES C CXX)

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    # The SDL2 library is distributed without configuration file for cmake on Windows
    # For this reason find_package command is not used. 
    # You must specify SDL2_DIR manually. SDL2_INCLUDE_DIRS and SDL2_LIBRARIES are set automatically 
    # https://stackoverflow.com/questions/28395833/using-sdl2-with-cmake
    set(SDL2_DIR "" CACHE PATH "The directory containing the SDL2 library")
    set(SDL2_INCLUDE_DIRS "${SDL2_DIR}/include")

    # Support both 32 and 64 bit builds
    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
      set(SDL2_LIBRARIES "${SDL2_DIR}/lib/x64/SDL2.lib;${SDL2_DIR}/lib/x64/SDL2main.lib")
      set(SDL2_LIBRARIES_DLL ${SDL2_DIR}/lib/x64/SDL2.dll)
    else ()
      set(SDL2_LIBRARIES "${SDL2_DIR}/lib/x86/SDL2.lib;${SDL2_DIR}/lib/x86/SDL2main.lib")
      set(SDL2_LIBRARIES_DLL ${SDL2_DIR}/lib/x86/SDL2.dll)
    endif ()

    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
    
else()
    find_package(SDL2 REQUIRED)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

file(GLOB SRCS_GameBackend ./GameBackend/src/*.cpp)
file(GLOB HEADERS_GameBackend ./GameBackend/include/*.h)

add_library(GameBackend STATIC ${SRCS_GameBackend} ${HEADERS_GameBackend})
target_include_directories(GameBackend PUBLIC GameBackend/include)

file(GLOB SRCS_GUI ./GUI/src/*.cpp)
file(GLOB HEADERS_GUI ./GUI/include/*.h)

add_library(GUI STATIC ${SRCS_GUI} ${HEADERS_GUI})
include_directories(GUI ${SDL2_INCLUDE_DIRS})
target_include_directories(GUI PUBLIC GUI/include)

file(GLOB SRCS_GameRunner ./GameRunner/src/*.cpp)
file(GLOB HEADERS_GameRunner ./GameRunner/include/*.h)

add_executable(GameRunner ${SRCS_GameRunner} ${HEADERS_GameRunner})

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
  add_definitions(-D WINDOWS)
else()
  add_definitions(-std=c++17)
endif()

target_link_libraries(GameRunner ${SDL2_LIBRARIES})
target_link_libraries(GameRunner GameBackend)
target_link_libraries(GameRunner GUI)
target_link_libraries(GameRunner Threads::Threads)
include_directories(GameRunner ${SDL2_INCLUDE_DIRS})
target_include_directories(GameRunner PUBLIC GameBackend/include)
target_include_directories(GameRunner PUBLIC GUI/include)
target_include_directories(GameRunner PUBLIC GameRunner/include)

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    file(TO_NATIVE_PATH ${SDL2_LIBRARIES_DLL} SOURCE_PATH_)
    
    # Post-build event for msvs to copy SDL2.dll
    add_custom_command(TARGET GameRunner POST_BUILD 
        COMMAND copy /Y ${SOURCE_PATH_} "$(SolutionDir)$(Configuration)"
    )
endif()
