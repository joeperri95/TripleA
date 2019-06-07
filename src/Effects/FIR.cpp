#include "../../include/Effects/FIR.hpp"

#include <iostream>

FIR::FIR(int numberOfTaps, float* bValues){
    this->numberOfTaps = numberOfTaps;
    this->bValues = bValues;
}

void FIR::apply(short *buffer, unsigned int sampleRate, int N){

    float *taps = (float *) malloc( this->numberOfTaps * sizeof(float));
    memset(taps, 0, this->numberOfTaps * sizeof(float));

    short y;

    for(int offset = 0; offset < N - 1; offset++){

        taps[0] = *(buffer + offset);

        y = 0;

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

        *(buffer + offset) = y;

    }

    free(taps);

}