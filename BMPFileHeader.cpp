#include "BMPFileHeader.h"

BMPFileHeader::BMPFileHeader(const BMPFileHeader &fh) {
    this->bfType = fh.bfType;
    this->bfSize = fh.bfSize;
    this->bfReserved1 = fh.bfReserved1;
    this->bfReserved2 = fh.bfReserved2;
    this->bfOffBits = fh.bfOffBits;
}