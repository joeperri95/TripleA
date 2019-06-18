
#ifndef _SINE_H_
#define _SINE_H_

#include "Tone.hpp"
#include <math.h>
#include <memory.h>
#include <iostream>

class Sine : public Tone {

public:
    Sine(
        double onTime,
        double offTIme, 
        double amplitude, 
        double freq);
    
    ~Sine();
    
    short callback(double t);

private:

    double frequency;

};

#endif