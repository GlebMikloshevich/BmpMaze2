#include "Pixel.h"

Pixel::Pixel(unsigned char b, unsigned char g, unsigned char r) {
    this->rgbBlue = b;
    this->rgbGreen = g;
    this->rgbRed = r;
}

void Pixel::init(int b, int g, int r) {
    this->rgbBlue =  (unsigned int)(b % 256);
    this->rgbGreen=  (unsigned int)(g % 256);
    this->rgbRed =  (unsigned int)(r % 256);
}

bool operator== (const Pixel &c1, const Pixel &c2){
    return (c1.rgbRed == c2.rgbRed && c1.rgbGreen == c2.rgbGreen && c1.rgbBlue == c2.rgbBlue);
}