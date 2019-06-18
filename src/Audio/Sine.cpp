
#include "../../include/Audio/Sine.hpp"

Sine::Sine(double onTime,
        double offTIme, 
        double amplitude, 
        double freq){

    this->amplitude = amplitude;
    this->frequency = freq;
    this->onTime = onTime;
    this->offTime = offTime;

}

Sine::~Sine(){
    
}

short Sine::callback(double t){
    short res = (short) (this->amplitude * INT16_MAX * sin((double) (this->frequency * TWOPI * t)));
    
    for(auto e : this->effects){
        e->apply(t, &res);
    }
    
    return res;
}

