
#include "Audio/Sine.hpp"

Sine::Sine(double onTime,
        double offTime, 
        double amplitude, 
        double freq){

    this->amplitude = amplitude;
    this->frequency = freq;
    this->onTime = onTime;
    this->offTime = offTime;

}

Sine::Sine(){
    this->onTime = 0.5;
    this->offTime = 1.5;
    this->amplitude = 0.5;
    this->frequency = 440;
}

Sine::~Sine(){
    
}

short Sine::callback(double t){
    
    short res = 0;

    if( (t >= this->onTime) && (t < this->offTime)){

        res = (short) (this->amplitude * INT16_MAX * sin((double) (this->frequency * TWOPI * t)));
        
        for(auto e : this->effects){
            e->apply(t, &res);
        }
    }

    return res;
}

