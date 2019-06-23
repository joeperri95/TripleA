
#include "Audio/Effects/Downsample.hpp"

#include <iostream>
#include <random>
#include <string.h>

Downsample::Downsample(int param){
    this->param = param;
    this->numTaps = param;
    this->taps = (short *) malloc(this->numTaps * sizeof(short));
    this->counter = 0;
    memset(this->taps, 0, this->numTaps * sizeof(short));

}

Downsample::~Downsample(){
    free(this->taps);
}

void Downsample::apply(double t, short *sample){
    
    //tap method would take a ton of n^2 memory

    /* 
    if(this->counter == this->param){

        this->counter = 0;
    }
    else{

    }

    taps[0] = *sample;

    for(int i = this->numTaps - 1; i > 0; i--){
        taps[i] = taps[i-1];
    }

    counter++; */

}