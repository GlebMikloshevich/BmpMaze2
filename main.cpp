#include <iostream>
#include "BMPReader.h"
#include "Pixel.h"
#include "Maze.h"
int main() {
    try {
        //making a file copy
        BMPReader m("C:\\Users\\GLEB\\CLionProjects\\BmpMaze\\maze.bmp");
        m.writeFile("C:\\Users\\GLEB\\CLionProjects\\BmpMaze\\test2.bmp");

        Maze maze("C:\\Users\\GLEB\\CLionProjects\\BmpMaze\\test2.bmp");
        maze.run();
    } catch (MazeException) {
        std::cout<<"error\n";
    }

}
