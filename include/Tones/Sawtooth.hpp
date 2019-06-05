#ifndef __SAWTOOTH_H__
#define __SAWTOOTH_H__

#include "Tone.hpp"
#include <string.h>

class Sawtooth : public Tone{

public:

    Sawtooth(unsigned int sampleRate, 
        unsigned int channels, 
        double duration, 
        double amplitude, 
        int harmonics,
        double freq);
    
    ~Sawtooth();


private:
    double frequency;
    int harmonics;
};



#endif