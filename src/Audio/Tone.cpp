#include "Audio/Tone.hpp"

Tone::Tone(){
    
}

Tone::~Tone(){

}

short Tone::callback(double t){

}

double Tone::getAmplitude(){
    return this->amplitude;
}

void Tone::setAmplitude(double amplitude){
    this->amplitude = amplitude;
}

void Tone::addEffect(Effect *e){
    this->effects.push_back(e);
}