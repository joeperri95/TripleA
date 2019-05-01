
#ifndef _SINE_H_
#define _SINE_H_

#include "Tone.hpp"
#include <math.h>
#include <memory.h>

class Sine : public Tone {

public:
    Sine(unsigned int sampleRate, 
        unsigned int channels, 
        double duration, 
        double amplitude, 
        double freq);
    
    ~Sine();
    short *getSamples();

private:
    double frequency;

};

#endif