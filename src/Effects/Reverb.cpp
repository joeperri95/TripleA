#include "../../include/Effects/Reverb.hpp"

Reverb::Reverb(float delayParam, float ampParam){
    this->delayParam = delayParam;
    this->ampParam = ampParam;
}

void Reverb::apply(short *buffer,unsigned int sampleRate, int N){

    int sampleDelay = (int) sampleRate * this->delayParam;

    for(int i = 0; i < N; i++){
        if(i < sampleDelay)
            continue;
        *(buffer+i)  = (short) ((1 - this->ampParam) **(buffer+i) + (this->ampParam * *(buffer + i - sampleDelay)));
    }

}