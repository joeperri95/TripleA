
#ifndef _SINE_H_
#define _SINE_H_

#include "Tone.hpp"
#include <math.h>
#include <memory.h>
#include <iostream>

class Sine : public Tone {

public:
    Sine(unsigned int sampleRate, 
        unsigned int channels, 
        double duration, 
        double amplitude, 
        double freq);
    
    Sine(Sine &other);

    ~Sine();
    
    double getFrequency();

private:
    double frequency;

};

#endif