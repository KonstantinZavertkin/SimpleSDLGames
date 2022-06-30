
SimpleSDLGames
==================================

The purpose of this project is learning C++ and SDL2 library. Minesweeper, Tetris and Snake are currently available.

## Installation instructions
Requirements:
 - CMake 3.8 or newer
 - Сompiler supporting C++17 or newer  
 - SDL2  
 - SDL2_ttf  
 
On Debian-based systems (including Ubuntu) can simply do:  

        sudo apt-get install libsdl2-2.0  
        sudo apt-get install libsdl2-dev  
        sudo apt-get install libsdl2-ttf-dev  

On Windows you need to download and install these libraries:  
&emsp; https://www.libsdl.org/download-2.0.php  
&emsp; https://github.com/libsdl-org/SDL_ttf/releases  

Building the executable file on Linux-based OS can be done using the following commands:  

        mkdir build  
        cd build  
        cmake ..  
        make all    

Run:  

        ./GameRunner  

Use cmake-gui to create solution for Visual Studio on Windows. Set 'Where is the source code' to root of this repository (For example, C:/SimpleSDLGames/). Set 'Where to build the binaries' to some new directory in root of repository (For example, C:/SimpleSDLGames/build)  
After 'Configure' stage cmake will requests for paths to header files and to compiled libraries (SDL2 and SDL2_ttf).  
You need to set up these variables:  
&emsp;SDL2_INCLUDE_DIRS  
&emsp;SDL2_LIBRARIES_DIRS  
&emsp;SDL2_TTF_INCLUDE_DIRS  
&emsp;SDL2_TTF_LIBRARIES_DIRS  
  
To run game after building, go to the directory with binaries (For example, C:/SimpleSDLGames/build/Debug) and run GameRunner.exe  
  
Tested on Debian 10 and Windows 10.    
  
## Screenshots  
![Main menu](/screenshots/0.png?raw=true "Main menu")
![Minesweeper](/screenshots/1.png?raw=true "Minesweeper")
![Tetris](/screenshots/2.png?raw=true "Tetris")
![Snake](/screenshots/3.png?raw=true "Snake")
