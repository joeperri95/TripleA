#include "../../include/Effects/DecayEffect.hpp"

#include <iostream>

DecayEffect::DecayEffect(double decayParam){

    if(decayParam > 0){
        std::cerr << "enter a parameter less than 0" << std::endl;
        throw 1;
    }
    this->decayParam = decayParam;
}

void DecayEffect::apply(short *buffer, unsigned int sampleRate, int N){

    for(int i = 0; i < N; i++){
        *(buffer + i) = (short) (*(buffer + i)*exp(((i * this->decayParam )/ (double) sampleRate)));
    }

}

