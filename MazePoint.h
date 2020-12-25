#ifndef BMPMAZE_MAZEPOINT_H
#define BMPMAZE_MAZEPOINT_H


class MazePoint {
public:
    int x, y, priority;
    MazePoint(int x, int y, int priority){
        this->x = x;
        this->y = y;

        this->priority = priority;
    }
    friend bool operator< (const MazePoint &p1, const MazePoint &p2){
        return p1.priority > p2.priority;
    }
    friend bool operator== (const MazePoint &p1, const MazePoint &p2){
        return p1.priority == p2.priority;
    }
    friend bool operator!= (const MazePoint &p1, const MazePoint &p2){
        return p1.priority != p2.priority;
    }

};


#endif //BMPMAZE_MAZEPOINT_H
