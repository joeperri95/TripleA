#ifndef __SQUARE_H__
#define __SQUARE_H__

#include "Tone.hpp"

class Square : public Tone{

public:
    Square(unsigned int sampleRate, 
        unsigned int channels, 
        double duration, 
        double amplitude, 
        int harmonics,
        double freq);

    ~Square();

private:
    double frequency;
    int harmonics;
};

#endif