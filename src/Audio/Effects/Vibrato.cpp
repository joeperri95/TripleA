#include "Audio/Effects/Vibrato.hpp"
#include <stdint.h>

Vibrato::Vibrato(double amplitude, double frequency, int modulation){
    this->frequency = frequency;
    this->amplitude = amplitude;
    this->modulation = modulation;
}


Vibrato::Vibrato(double amplitude, double frequency){
    this->frequency = frequency;
    this->amplitude = amplitude;

    this->modulation = 65;
}

void Vibrato::apply(double t, short *sample){

    //need to look at other samples

/* 
        short modulatedComponent = (short) (this->amplitude * *(sample + (int) (this->modulation * sin(TWOPI * t * this->frequency ))));  
        short normalComponent = (short) ((1-this->amplitude) * *sample);

        *(sample) = normalComponent + modulatedComponent;
 */        

}