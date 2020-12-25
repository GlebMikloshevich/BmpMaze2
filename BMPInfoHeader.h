#ifndef BMPMAZE_BMPINFOHEADER_H
#define BMPMAZE_BMPINFOHEADER_H


class BMPInfoHeader {
private:
    unsigned int   biSize; //info header size
    unsigned int   biWidth; //image width
    unsigned int   biHeight; //image height
    unsigned short biPlanes;
    unsigned short biBitCount;
    unsigned int   biCompression;
    unsigned int   biSizeImage;
    int            biXPelsPerMeter;
    int            biYPelsPerMeter;
    unsigned int   biClrUsed;
    unsigned int   biClrImportant;

public:
    BMPInfoHeader(){};
    BMPInfoHeader(const BMPInfoHeader& fi);

    friend class BMPReader;
    friend class Maze;
};


#endif //BMPMAZE_BMPINFOHEADER_H
