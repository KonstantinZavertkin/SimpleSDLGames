cmake_minimum_required(VERSION 3.0)

project(SnakeGame VERSION 0.1 LANGUAGES C CXX)

find_package(SDL2 REQUIRED)

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
add_definitions(-std=c++17)

target_link_libraries(GameRunner ${SDL2_LIBRARIES})
target_link_libraries(GameRunner GameBackend)
target_link_libraries(GameRunner GUI)

include_directories(GameRunner ${SDL2_INCLUDE_DIRS})
target_include_directories(GameRunner PUBLIC GameBackend/include)
target_include_directories(GameRunner PUBLIC GUI/include)
target_include_directories(GameRunner PUBLIC GameRunner/include)

install(TARGETS GameRunner DESTINATION ./bin)
