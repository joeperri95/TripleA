#include "Audio/Effects/DecayEffect.hpp"

#include <iostream>

DecayEffect::DecayEffect(double decayParam, double onTime, double offTime){

    this->onTime = onTime;
    this->offTime = offTime;

    if(decayParam > 0){
        std::cerr << "enter a parameter less than 0" << std::endl;
        throw 1;
    }
    
    this->decayParam = decayParam;
}

void DecayEffect::apply(double t, short *sample){

    if(t >= this->offTime || t < this->onTime)
        return;
    else{
        *sample = (short) (*sample * exp( (t - this->onTime) * this->decayParam));    
    }
}

