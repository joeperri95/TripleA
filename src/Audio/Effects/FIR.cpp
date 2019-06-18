#include "Audio/Effects/FIR.hpp"

#include <iostream>

FIR::FIR(int numberOfTaps, float* bValues){
    this->numberOfTaps = numberOfTaps;
    this->bValues = bValues;
    this->taps = (float *) malloc( this->numberOfTaps * sizeof(float));
    memset(this->taps, 0, this->numberOfTaps * sizeof(float));

}

void FIR::apply(double t, short *sample){
    
    short y = 0;

    taps[0] = *(sample);

    //clips without this
    //need to test with range of amplitudes
    int fixer = 2;

    //accumulate
    for(int i = 0; i < this->numberOfTaps; i++){
        y += (short) ((*(this->bValues + i)) * taps[i] / fixer);
    }

    //shift taps
    for(int i = this->numberOfTaps - 1; i > 0; i--){
        taps[i] = taps[i-1];
    }

    *sample = y;
    
}