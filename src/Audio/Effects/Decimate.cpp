#include "Audio/Effects/Decimate.hpp"

Decimate::Decimate(int factor){
    this->factor = factor;

}

Decimate::~Decimate(){

}

void Decimate::apply(double t, short *sample){

    *sample = (INT16_MAX / this->factor) * *sample >> this->factor;

}