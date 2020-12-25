#ifndef BMPMAZE_BMPFILEHEADER_H
#define BMPMAZE_BMPFILEHEADER_H


class BMPFileHeader {
public:
    unsigned int    bfSize; //file size
    unsigned int    bfOffBits; //offset
    unsigned short  bfType; //file signature
    unsigned short  bfReserved1;
    unsigned short  bfReserved2;
public:
    BMPFileHeader(){};
    BMPFileHeader(const BMPFileHeader& fh);
    friend class BMPReader;
    friend class Maze;

};


#endif //BMPMAZE_BMPFILEHEADER_H
