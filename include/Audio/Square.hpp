#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Tone.hpp"

class Square : public Tone{

public:
    Square(
        double onTime,
        double offTime, 
        double amplitude, 
        int harmonics,
        double freq);

    ~Square();

    short callback(double t);

private:
    double frequency;
    int harmonics;
};

#endif