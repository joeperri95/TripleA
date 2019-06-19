
#include "../../include/Audio/Square.hpp"

Square::Square(double onTime,
        double offTime, 
        double amplitude, 
        int harmonics,
        double freq){

    this->amplitude = amplitude;
    this->frequency = freq;
    this->harmonics = harmonics;

}

Square::~Square(){
    
}

short Square::callback(double t){
    
    short res = 0;
    
    for(int i=1; i < this->harmonics; i += 2){
        
        res = (short) (res + (this->amplitude / i) * INT16_MAX * sin((double) (this->frequency * t * i * TWOPI)));
        
    }

    for(auto e : this->effects){
        e->apply(t, &res);
    }

    return res;

}
