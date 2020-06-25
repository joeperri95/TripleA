#ifndef __SAWTOOTH_H__
#define __SAWTOOTH_H__

#include "Tone.hpp"
#include <string.h>

class Sawtooth : public Tone
{

public:
    Sawtooth(
        double onTime,
        double offTime,
        double amplitude,
        int harmonics,
        double freq);

    ~Sawtooth();

    short *callback(double t);

private:
    double frequency;
    int harmonics;
};

#endif