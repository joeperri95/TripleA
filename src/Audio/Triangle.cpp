
#include "../../include/Audio/Triangle.hpp"

Triangle::Triangle(double onTime,
        double offTime, 
        double amplitude, 
        int harmonics,
        double freq){

    this->amplitude = amplitude;
    this->frequency = freq;
    this->harmonics = harmonics;

}

Triangle::~Triangle(){
    
}

short Triangle::callback(double t){

    short res = 0;

    for(int i=0; i < harmonics; i++){
        
        if(i & 0x1){
            res = (short) (res + ((this->amplitude / (pow(2*i+1, 2))) * INT16_MAX * sin( (double) (this->frequency * t * (2*i + 1) * TWOPI) )));
        }
        else{
            res = (short) (res - ((this->amplitude / (pow(2*i+1, 2))) * INT16_MAX * sin( (double) (this->frequency * t * (2*i + 1) * TWOPI)  )));
        }
    }

    for(auto e : this->effects){
        e->apply(t, &res);
    }

    return res;

}

