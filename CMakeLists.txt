cmake_minimum_required(VERSION 3.17)
project(BmpMaze)

set(CMAKE_CXX_STANDARD 17)

add_executable(BmpMaze main.cpp BMPReader.cpp BMPReader.h BMPFileHeader.cpp BMPFileHeader.h BMPInfoHeader.cpp BMPInfoHeader.h Pixel.cpp Pixel.h Maze.cpp Maze.h MazePoint.cpp MazePoint.h)