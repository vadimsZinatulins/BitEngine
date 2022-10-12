# BitEngine
This is my own game engine library that I'm developing from scratch. It is still a __WIP__
# Dependencies
## C++ Compiler
You need a C++ compiler (for example clang or gcc) to this project (as well as generated project).
## CMake
To build this project you need CMake. Also to build the generated project you also need CMake. Assuming that you are running it from ubuntu you can execute the following command:
```bash
sudo apt-get install cmake
```
## SDL2
SDL2 is not a direct dependecy of this project but the generated project uses SDL2 so to take advantage of the generated project SDL2 is required. Assuming that you are running it from ubuntu you can execute the following command:
```bash
sudo apt-get install libsdl2-dev
```
## SimpleTaskManager
This is a library that I've created to manage asynchronous task. It can be found [here](https://github.com/vadimsZinatulins/SimpleTaskManager).
# Installation
To build and install this library you can run the following commands:
```bash
cmake -B build
cmake --build build/
sudo cmake --install build/
```
