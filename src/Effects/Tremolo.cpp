#include "../../include/Effects/Tremolo.hpp"

Tremolo::Tremolo(double amplitude, double frequency){
    this->amplitude = amplitude;
    this->frequency = frequency;
}

void Tremolo::apply(short *buffer, unsigned int sampleRate, int N){

    for(int i = 0; i < N; i++){
        short tremoloPart = (short) (this->amplitude * (*(buffer + i) * ( (sin(TWOPI * i * this->frequency / sampleRate)))));
        short normalPart = (short) ((1 - this->amplitude) * *(buffer + i));
        *(buffer + i) =  (short) (tremoloPart + normalPart);

    }


}