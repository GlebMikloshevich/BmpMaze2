#include "BMPReader.h"

BMPReader::BMPReader() {}

BMPReader::BMPReader(char* s) {
    this->init(s);
}

BMPReader::BMPReader(const BMPReader &br) {

    this->fh = br.fh;
    this->fi = br.fi;
    this->pixels = new Pixel*[this->fi.biHeight];
    for (int i = 0; i < fi.biHeight; i++){
        this->pixels[i] = new Pixel[this->fi.biWidth];

        for (int j = 0; j < this->fi.biWidth; j++)
            this->pixels[i][j] = br.pixels[i][j];
    }
}

BMPReader::~BMPReader() {
    for (int i = 0; i < this->fi.biHeight; i++)
        delete[] this->pixels[i];
    delete[] pixels;
}

BMPReader::BMPReader(BMPFileHeader bf, BMPInfoHeader bi, Pixel **bmp) {
    this->fh = bf;
    this->fi = bi;

    this->pixels = new Pixel*[this->fi.biHeight];
    for (int i = 0; i < fi.biHeight; i++){
        this->pixels[i] = new Pixel[this->fi.biWidth];
        for (int j = 0; j < this->fi.biWidth; j++)
            this->pixels[i][j] = bmp[i][j];
    }
}

unsigned int BMPReader::getwidth() {
    return this->fi.biWidth;
}

unsigned int BMPReader::getHeight() {
    return this->fi.biHeight;
}


void BMPReader::init(char* s) {
    FILE* stream = fopen(s, "rb");

    if (!stream) {
        std::cout<<"file open error\n";
        throw MazeException();
    }


    //reading BMP file
    try {

        //reading BMP file header
        fread(&this->fh.bfType, 2, 1, stream); //error. 16 bytes
        fread(&this->fh.bfSize, 4, 1, stream);
        fread(&this->fh.bfReserved1, 2, 1, stream);
        fread(&this->fh.bfReserved2, 2, 1, stream);
        fread(&this->fh.bfOffBits, 4, 1, stream);

        if (this->fh.bfType != 0x4D42) {
            std::cout<<"file signature error\n";
            throw MazeException();
        }

        //reading BMP info header
        fread(&this->fi, sizeof(BMPInfoHeader), 1, stream);

        //creating 2D array of pixels
        this->pixels = new Pixel*[this->fi.biHeight];
        for (int i = 0; i < this->fi.biHeight; i++)
            this->pixels[i] = new Pixel[this->fi.biWidth];

       //reading bitmap
        for (int i = 0; i < this->fi.biHeight; i++)
            for (int j = 0; j < this->fi.biWidth; j++)
                fread(&this->pixels[i][j], sizeof(Pixel), 1, stream);

        fclose(stream);

    } catch (std::ifstream::failure e) {
        std::cout<<"reading exception\n"; //std::cerr?
    }

}

void BMPReader::writeFile(char *s) {
    FILE* f = fopen(s, "wb");

    //writing bmp file header
    fwrite(&this->fh.bfType, 2 , 1, f);
    fwrite(&this->fh.bfSize, 4 , 1, f);
    fwrite(&this->fh.bfReserved1, 2 , 1, f);
    fwrite(&this->fh.bfReserved2, 2 , 1, f);
    fwrite(&this->fh.bfOffBits, 4 , 1, f);

    //writing bmp info header
    fwrite(&this->fi, 40 , 1, f);

    //writing pixels
    for (int i = 0; i < this->fi.biHeight; i++) {
        for (int j = 0; j < this->fi.biWidth; j++) {
            fwrite(&this->pixels[i][j], 3, 1, f);
            //TODO make paddings. for now work only with width % 4 = 0
        }
    }

    fclose(f);
}
