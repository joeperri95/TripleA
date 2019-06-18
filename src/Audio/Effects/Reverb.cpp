#include "Audio/Effects/Reverb.hpp"

Reverb::Reverb(float delayParam, float ampParam){
    this->delayParam = delayParam;
    this->ampParam = ampParam;
}

void Reverb::apply(double t, short *sample){

    //need to look at other samples

    /* 
    *(sample)  = (short) ((1 - this->ampParam) * *(sample) + (this->ampParam * *(sample + (int) (t - this->delayParam))));
     */

}