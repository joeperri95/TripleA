#include "Audio/Effects/Tremolo.hpp"

Tremolo::Tremolo(double amplitude, double frequency){
    this->amplitude = amplitude;
    this->frequency = frequency;
}

void Tremolo::apply(double t, short *sample){
    
        short tremoloPart = (short) (this->amplitude * (*(sample) * (sin(TWOPI * t * this->frequency ))));
        short normalPart = (short) ((1 - this->amplitude) * *(sample));
        *(sample) =  (short) (tremoloPart + normalPart);

}