#include "Audio/Effects/Vibrato.hpp"
#include <stdint.h>
#include <string.h>
#include <iostream>

Vibrato::Vibrato(double amplitude, double frequency, int numTaps, int modulation){
    this->frequency = frequency;
    this->amplitude = amplitude;
    this->modulation = modulation;
    this->numTaps = numTaps;
    this->taps = (short *) malloc(this->numTaps * sizeof(double));
    memset(this->taps, 0, this->numTaps * sizeof(double));
}


Vibrato::Vibrato(double amplitude, double frequency, int numTaps){
    this->frequency = frequency;
    this->amplitude = amplitude;
    this->modulation = 65; //sounds roughly right
    this->numTaps = numTaps;
    this->taps = (short *) malloc(this->numTaps * sizeof(short));
    memset(this->taps, 0, this->numTaps * sizeof(short));
    
}

Vibrato::~Vibrato(){
    free(this->taps);
}

void Vibrato::apply(double t, short *sample){

    this->taps[0] = *sample;

    //need to look at other samples

    int phase = (int) ((this->numTaps / 2) * sin(TWOPI * t * this->frequency) + this->numTaps / 2);

    short modulatedComponent = (short) (this->amplitude * *(this->taps + phase));  
    short normalComponent = (short) ((1-this->amplitude) * *(this->taps + this->numTaps / 2));

    *(sample) = normalComponent + modulatedComponent;
    
    for(int i = this->numTaps - 1; i > 0; i--){
        this->taps[i] = this->taps[i-1];
    }

}