#include "../../include/Effects/Vibrato.hpp"
#include <stdint.h>

Vibrato::Vibrato(unsigned int frequency){
    this->frequency = frequency;
}

void Vibrato::apply(short *buffer, unsigned int sampleRate, int N){

    
    double amplitude = 0.1;
    int onePeriod = this->frequency / sampleRate;
    int offset = 0;
    short *carrier = (short *) malloc(onePeriod * sizeof(short));        
    
    //build modulating carrier
    for(int i = 0; i < onePeriod; i++){
        *(carrier+i) = (short) (INT16_MAX * amplitude * sin(TWOPI * (onePeriod - i) * this->frequency));
    }

    //build final waveform
    for(int i = 0; i < N; i++){
        *(buffer + i) = *(buffer + i);
        
        offset++;
    }   


}