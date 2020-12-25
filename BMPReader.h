#include "iostream"
#include "BMPFileHeader.h"
#include "BMPInfoHeader.h"
#include "fstream"
#include "Pixel.h"

#ifndef BMPMAZE_BMPREADER_H
#define BMPMAZE_BMPREADER_H

class MazeException{};
class BMPReader {
public:
    Pixel **pixels;

    BMPFileHeader fh;
    BMPInfoHeader fi;
    char* name = "";

    BMPReader();
    BMPReader(char* s);
    BMPReader(const BMPReader& br);
    BMPReader(BMPFileHeader bf, BMPInfoHeader bi, Pixel **bmp);

    ~BMPReader();

    unsigned int getwidth();
    unsigned int getHeight();
    void init(char* s);
    void writeFile(char* s);

    friend class Maze;
};


#endif //BMPMAZE_BMPREADER_H
