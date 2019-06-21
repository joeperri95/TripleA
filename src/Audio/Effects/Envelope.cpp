#include "Audio/Effects/Envelope.hpp"
#include <iostream>

Envelope::Envelope(double attackTime,
        double releaseTime,
        double attackParam,
        double decayParam,
        double releaseParam,
        double attackLevel,
        double sustainLevel)
{

        this->attackTime = attackTime;
        this->releaseTime = releaseTime;
        this->attackParam = attackParam;
        this->decayParam = decayParam;
        this->releaseParam = releaseParam;
        this->attackLevel = attackLevel; 
        this->sustainLevel = sustainLevel; 

}

Envelope::~Envelope(){

}

void Envelope::apply(double t, short *sample){

    double normalizedTime = t - attackTime;
    double temp = 1.0;

    if(normalizedTime < this->attackParam){
        temp = (normalizedTime / this->attackParam) * attackLevel;
    }
    else if((normalizedTime >= this->attackParam) && (normalizedTime < this->decayParam)){
        temp = attackLevel - ((normalizedTime - attackParam) / this->decayParam) * sustainLevel;
    }
    else if((normalizedTime >= this->decayParam) && (normalizedTime < this->releaseTime)){
        temp = sustainLevel;
    }
    else if((normalizedTime >= this->releaseTime) && (normalizedTime < this->releaseParam)){
        temp = sustainLevel - ((normalizedTime - this->releaseTime) / this->releaseParam);
    }
    else{
        temp = 0;
    }

    *sample = (short) (*sample * temp);

}