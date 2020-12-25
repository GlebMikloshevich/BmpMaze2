#include "BMPInfoHeader.h"

BMPInfoHeader::BMPInfoHeader(const BMPInfoHeader &fi) {
    this->biSize = fi.biSize;
    this->biWidth = fi.biWidth;
    this->biHeight = fi.biHeight;
    this->biPlanes = fi.biPlanes;
    this->biBitCount = fi.biBitCount;
    this->biCompression = fi.biCompression;
    this->biSizeImage = fi.biSizeImage;
    this->biXPelsPerMeter = fi.biXPelsPerMeter;
    this->biYPelsPerMeter = fi.biYPelsPerMeter;
    this->biClrUsed = fi.biClrUsed;
    this->biClrImportant = fi.biClrImportant;
}