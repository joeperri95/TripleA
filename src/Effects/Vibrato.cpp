#include "../../include/Effects/Vibrato.hpp"
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

void Vibrato::apply(short *buffer, unsigned int sampleRate, int N){

    for(int i = 0; i < N; i++){

        short modulatedComponent = (short) (this->amplitude * *(buffer + i + (int) (this->modulation * sin(TWOPI * i * this->frequency / sampleRate))));  
        short normalComponent = (short) ((1-this->amplitude) * *(buffer + i));

        *(buffer + i) = normalComponent + modulatedComponent;
        
    }   

}