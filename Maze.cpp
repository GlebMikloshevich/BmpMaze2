#include "Maze.h"

Maze::Maze() {}

Maze::Maze(char* s){
    this->init(s);
}

Maze::~Maze() {
    delete [] this->filePath;
}

void Maze::init(char *s) {
    this->reader.init(s);
    filePath = s;
    //std::cout<<"\nfile path is: "<<s<<'\n';
    this->isInit = true;

    this->wall.init(0, 0, 0);
    this->start.init(36, 28, 237);
    this->finish.init(76, 177, 34);

}
int Maze::get_priority(int x, int y) {
    return abs(this->finish_point.first - x +1) + abs(this->finish_point.second - y +1);
}

void Maze::prepareMaze() {
    if (!this->isInit){
        std::cout<<"Maze was not initialized\n";
        throw MazeException();
    }

    if (this->reader.fi.biWidth < 1 || this->reader.fi.biHeight < 1){
        std::cout<<"image height or width < 1\n";
        throw MazeException();
    }

    this->start_point.first = -1;
    this->finish_point.first = -1;

    this->simpleMaze = new int*[this->reader.fi.biHeight+2];
    for (int i = 0; i < this->reader.fi.biHeight+2; i++)
        this->simpleMaze[i] = new int[this->reader.fi.biWidth+2];

    //making borders
    for (int i = 0; i < this->reader.fi.biHeight; i++){
        this->simpleMaze[i][0] = -1;
        this->simpleMaze[i][this->reader.fi.biWidth+1] = -1;
    }
    for (int i = 0; i < this->reader.fi.biWidth; i++) {
        this->simpleMaze[0][i] = -1;
        this->simpleMaze[this->reader.fi.biHeight+1][i] = -1; // error with fi.biHeight
    }
    //
    for (int i = 0; i < this->reader.fi.biHeight; i++){
        for (int j = 0; j < this->reader.fi.biWidth; j++) {

            if (this->reader.pixels[i][j] == this->wall){
                this->simpleMaze[i+1][j+1] = -1;
            } else {
                this->simpleMaze[i+1][j+1] = 0;
                //searching for start and finish points
                if (this->reader.pixels[i][j] == this->start) {
                    this->start_point.first = i+1;
                    this->start_point.second = j+1;
                }
                if (this->reader.pixels[i][j] == this->finish){
                    //std::cout<<"finish point"<<i<<' '<<j<<'\n';
                    this->finish_point.first = i+1;
                    this->finish_point.second = j+1;
                }
            }
        }
    }

    if (start_point.first == -1|| finish_point.first == -1){
        std::cout<<"no start or finish points\n";
        throw MazeException();
    }
    //std::cout<<"maze prepared\n";
}

void Maze::dijkstra() {

    std::priority_queue<MazePoint> queue;
    simpleMaze[start_point.first][start_point.second] = 1;
    queue.push(MazePoint(start_point.first, start_point.second, 1));
    bool search = true;

    while(search) {
        if (queue.empty()) {
            std::cout<<"no path\n";
            throw MazeException();
        }

        MazePoint a = queue.top();
        queue.pop();
        //std::cout<<a.x<<' '<<a.y<<' '<<a.priority<<' '<<simpleMaze[a.x][a.y]<<'\n';

        if (a.x == this->finish_point.first && a.y == this->finish_point.second)
            search = false;

        //can check value in cycle, but this way i have to add values into queue
        if (simpleMaze[a.x - 1][a.y] == 0){
            simpleMaze[a.x - 1][a.y] = simpleMaze[a.x][a.y] + 1;
            queue.push(MazePoint(a.x-1, a.y, simpleMaze[a.x][a.y] +1));
            //std::cout<<" -10 ";
        }

        if (simpleMaze[a.x + 1][a.y] == 0){
            simpleMaze[a.x + 1][a.y] = simpleMaze[a.x][a.y] + 1;
            queue.push(MazePoint(a.x + 1, a.y, simpleMaze[a.x][a.y] +1));
            //std::cout<<" +10 ";
        }

        if (simpleMaze[a.x][a.y - 1] == 0){
            simpleMaze[a.x][a.y - 1] = simpleMaze[a.x][a.y] + 1;
            queue.push(MazePoint(a.x, a.y-1, simpleMaze[a.x][a.y] +1));
            //std::cout<<" 0-1 ";
        }

        if (simpleMaze[a.x][a.y + 1] == 0){
            simpleMaze[a.x][a.y + 1] = simpleMaze[a.x][a.y] + 1;
            queue.push(MazePoint(a.x, a.y+1, simpleMaze[a.x][a.y] +1));
            //std::cout<<" 0+1 ";
        }
    }
}

void Maze::Astar(){
    std::priority_queue<MazePoint> queue;
    simpleMaze[start_point.first][start_point.second] = 1;
    queue.push(MazePoint(start_point.first, start_point.second, 1));
    bool search = true;

    while(search) {
        if (queue.empty()) {
            std::cout<<"no path\n";
            throw MazeException();
        }

        MazePoint a = queue.top();
        queue.pop();
        //std::cout<<a.x<<' '<<a.y<<' '<<a.priority<<' '<<simpleMaze[a.x][a.y]<<'\n';

        if (a.x == this->finish_point.first && a.y == this->finish_point.second)
            search = false;

        //can check value in cycle, but this way i have to add values into queue
        if (simpleMaze[a.x - 1][a.y] == 0){
              simpleMaze[a.x - 1][a.y] = simpleMaze[a.x][a.y] + 1;
              queue.push(MazePoint(a.x-1, a.y, this->get_priority(a.x-1, a.y)));
              //std::cout<<" -10 ";
        }

        if (simpleMaze[a.x + 1][a.y] == 0){
            simpleMaze[a.x + 1][a.y] = simpleMaze[a.x][a.y] + 1;
            queue.push(MazePoint(a.x + 1, a.y, this->get_priority(a.x+1, a.y)));
            //std::cout<<" +10 ";
        }

        if (simpleMaze[a.x][a.y - 1] == 0){
            simpleMaze[a.x][a.y - 1] = simpleMaze[a.x][a.y] + 1;
            queue.push(MazePoint(a.x, a.y-1, this->get_priority(a.x, a.y-1)));
            //std::cout<<" 0-1 ";
        }

        if (simpleMaze[a.x][a.y + 1] == 0){
            simpleMaze[a.x][a.y + 1] = simpleMaze[a.x][a.y] + 1;
            queue.push(MazePoint(a.x, a.y+1, this->get_priority(a.x, a.y+1)));
            //std::cout<<" 0+1 ";
        }
    }
    //std::cout<<"pixels to write "<<simpleMaze[this->finish_point.first][this->finish_point.second]<<'\n';
}

void Maze::drawPath() {
    Pixel pathColor(160, 0, 255);
    std::pair<int, int> curPoint;
    curPoint.first = this->finish_point.first;
    curPoint.second = this->finish_point.second;
    //std::cout<<"draw path\n";
    while(curPoint.first != start_point.first || curPoint.second != start_point.second){
        //std::cout<<simpleMaze[curPoint.first][curPoint.second]<<' ';
        if (simpleMaze[curPoint.first][curPoint.second] - simpleMaze[curPoint.first - 1][curPoint.second] == 1)
            curPoint.first -= 1;
        else if (simpleMaze[curPoint.first][curPoint.second] - simpleMaze[curPoint.first + 1][curPoint.second] == 1)
            curPoint.first += 1;
        else if (simpleMaze[curPoint.first][curPoint.second] - simpleMaze[curPoint.first][curPoint.second -1 ] == 1)
            curPoint.second -= 1;
        else if (simpleMaze[curPoint.first][curPoint.second] - simpleMaze[curPoint.first][curPoint.second + 1] == 1)
            curPoint.second += 1;

        this->reader.pixels[curPoint.first-1][curPoint.second-1] = pathColor;
    }
    //std::cout<<"end";
}
void Maze::saveFile() {
    this->reader.writeFile(this->filePath);
}

void Maze::run() {
    this->prepareMaze();
    this->dijkstra();
    //this->Astar();
    this->drawPath();
    this->saveFile();
}


