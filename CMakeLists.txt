cmake_minimum_required(VERSION 3.0)

project(SimpleSDL2Games VERSION 0.1 LANGUAGES C CXX)

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    # The SDL2 library is distributed without configuration file for cmake on Windows
    # For this reason find_package command is not used. 
    # You must specify SDL2_INCLUDE_DIRS and SDL2_LIBRARIES, SDL2_TTF_INCLUDE_DIRS and SDL2_TTF_LIBRARIES_DIRS manually
    # https://stackoverflow.com/questions/28395833/using-sdl2-with-cmake
    set(SDL2_INCLUDE_DIRS "" CACHE PATH "The directory containing the SDL2 headers (include directory)")
    set(SDL2_LIBRARIES_DIRS "" CACHE PATH "The directory containing the SDL2 libraries (.lib and .dll files)")

    set(SDL2_TTF_INCLUDE_DIRS "" CACHE PATH "The directory containing the SDL_ttf headers (include directory)")
    set(SDL2_TTF_LIBRARIES_DIRS "" CACHE PATH "The directory containing the SDL_ttf libraries (.lib and .dll files)")

    set(SDL2_LIBRARIES "${SDL2_LIBRARIES_DIRS}/SDL2.lib;${SDL2_LIBRARIES_DIRS}/SDL2main.lib")
    set(SDL2_LIBRARIES_DLL ${SDL2_LIBRARIES_DIRS}/)
    set(SDL2_TTF_LIBRARIES "${SDL2_TTF_LIBRARIES_DIRS}/SDL2_ttf.lib")
    set(SDL2_TTF_LIBRARIES_DLL ${SDL2_TTF_LIBRARIES_DIRS}/)

    string(STRIP "${SDL2_LIBRARIES}" SDL2_LIBRARIES)
    
else()
    find_package(SDL2 REQUIRED)
    set(SDL2_TTF_LIBRARIES libSDL2_ttf-2.0.so)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

file(GLOB HEADERS_Common ./Common/include/*.h)

file(GLOB SRCS_GameBackend ./GameBackend/src/*.cpp)
file(GLOB HEADERS_GameBackend ./GameBackend/include/*.h)

add_library(GameBackend STATIC ${SRCS_GameBackend} ${HEADERS_GameBackend})
target_include_directories(GameBackend PUBLIC Common/include)
target_include_directories(GameBackend PUBLIC GameBackend/include)

file(GLOB SRCS_GUI ./GUI/src/*.cpp)
file(GLOB HEADERS_GUI ./GUI/include/*.h)

add_library(GUI STATIC ${SRCS_GUI} ${HEADERS_GUI})
include_directories(GUI ${SDL2_INCLUDE_DIRS})
include_directories(GUI ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(GUI PUBLIC Common/include)
target_include_directories(GUI PUBLIC GUI/include)
target_link_libraries(GUI ${SDL2_TTF_LIBRARIES})
target_link_libraries(GUI ${FT_LIBRARIES})

file(GLOB SRCS_GameRunner ./GameRunner/src/*.cpp)
file(GLOB HEADERS_GameRunner ./GameRunner/include/*.h)

add_executable(GameRunner ${SRCS_GameRunner} ${HEADERS_GameRunner})

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    add_definitions(-D WINDOWS)
    add_definitions(/std:c++17)
else()
    add_definitions(-std=c++17)
endif()

target_link_libraries(GameRunner ${SDL2_LIBRARIES})
target_link_libraries(GameRunner ${SDL2_TTF_LIBRARIES})
target_link_libraries(GameRunner GameBackend)
target_link_libraries(GameRunner GUI)
include_directories(GameRunner ${SDL2_INCLUDE_DIRS})
include_directories(GameRunner ${SDL2_TTF_INCLUDE_DIRS})
target_include_directories(GameRunner PUBLIC Common/include)
target_include_directories(GameRunner PUBLIC GameBackend/include)
target_include_directories(GameRunner PUBLIC GUI/include)
target_include_directories(GameRunner PUBLIC GameRunner/include)

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    file(TO_NATIVE_PATH ${SDL2_LIBRARIES_DLL} SOURCE_PATH_)
    file(TO_NATIVE_PATH ${SDL2_TTF_LIBRARIES_DLL} SOURCE_PATH_TTF_)
    
    # Post-build event for msvs to copy SDL2.dll
    add_custom_command(TARGET GameRunner POST_BUILD 
        COMMAND xcopy /y /e ${SOURCE_PATH_} "$(SolutionDir)$(Configuration)\\*.*"
    )
    
    # Post-build event for msvs to copy SDL2.dll
    add_custom_command(TARGET GameRunner POST_BUILD 
        COMMAND xcopy /y /e ${SOURCE_PATH_TTF_} "$(SolutionDir)$(Configuration)\\*.*"
    )
	
	# Post-build event for msvs to copy resources
    add_custom_command(TARGET GameRunner POST_BUILD 
        COMMAND xcopy /y /e "$(SolutionDir)\\..\\resources\\" "$(SolutionDir)$(Configuration)\\resources\\*.*"
    )
    
    # set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GameRunner)
else()
    target_link_libraries(GameRunner Threads::Threads)
    
    add_custom_command(TARGET GameRunner POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/resources/ $<TARGET_FILE_DIR:GameRunner>/resources/)
endif()
