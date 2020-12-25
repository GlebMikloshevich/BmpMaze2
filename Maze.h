#include "BMPReader.h"
#include "MazePoint.h"
#include <utility>
#include <queue>

#ifndef BMPMAZE_MAZE_H
#define BMPMAZE_MAZE_H

class MazeSolverException{};
class Maze {
private:
    bool isInit = false;
    char* filePath;
    int** simpleMaze;

    std::pair<int, int> start_point;
    std::pair<int, int> finish_point;

    unsigned char t = 0;
    Pixel wall;
    Pixel start;
    Pixel finish;

    BMPReader reader;

    int get_priority(int x, int y);

    void prepareMaze();
    void dijkstra();
    void Astar();
    void drawPath();
    void saveFile();

public:
    Maze();
    Maze(char* s);
    ~Maze();
    void init(char* s);

    void run();

};


#endif //BMPMAZE_MAZE_H
