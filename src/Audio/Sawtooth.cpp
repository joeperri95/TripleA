#include "../../include/Audio/Sawtooth.hpp"


Sawtooth::Sawtooth(double onTime,
        double offTime, 
        double amplitude, 
        int harmonics,
        double freq){

    
    this->amplitude = amplitude;
    this->frequency = freq;
    this->harmonics = harmonics;
    this->onTime = onTime;
    this->offTime = offTime;

}

Sawtooth::~Sawtooth(){
    
}

short Sawtooth::callback(double t){
    
    short res = 0;
    
    if( (t >= this->onTime) && (t < this->offTime)){
        for(int i=1; i < harmonics; i++){
            
            if(i & 0x1){
                
                res = (short) (res + this->amplitude / (PI * i) * INT16_MAX * sin( (double) (this->frequency * t * i * TWOPI)));
                
            }
            else{
                
                res = (short) (res - this->amplitude / (PI * i) * INT16_MAX * sin( (double) (this->frequency * t * i * TWOPI)));
                
            }
    
        }

        for(auto e : this->effects){
            e->apply(t, &res);
        }
    }

    return res;
}

