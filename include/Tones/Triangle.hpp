#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Tone.hpp"

class Triangle : public Tone{

public:
    Triangle(unsigned int sampleRate, 
        unsigned int channels, 
        double duration, 
        double amplitude, 
        int harmonics,
        double freq);

    ~Triangle();

private:
    double frequency;
    int harmonics;
};

#endif