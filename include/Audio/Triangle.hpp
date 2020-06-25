#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Tone.hpp"

class Triangle : public Tone
{

public:
    Triangle(
        double onTime,
        double offTime,
        double amplitude,
        int harmonics,
        double freq);

    ~Triangle();
    short *callback(double t);

private:
    double frequency;
    int harmonics;
};

#endif