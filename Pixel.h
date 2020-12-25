#ifndef BMPMAZE_PIXEL_H
#define BMPMAZE_PIXEL_H


class Pixel {
public:
    unsigned char  rgbBlue;          /* Blue value */
    unsigned char  rgbGreen;         /* Green value */
    unsigned char  rgbRed;           /* Red value */

    Pixel(){};
    Pixel(unsigned char b, unsigned char g, unsigned char r);
    friend bool operator== (const Pixel &c1, const Pixel &c2);
    void init(int b, int g, int r);


};




#endif //BMPMAZE_PIXEL_H
