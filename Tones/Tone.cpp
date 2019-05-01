
#include "Tone.hpp"

Tone::Tone(){

}

Tone::~Tone(){

}

unsigned int Tone::getChannels(){
    return this->channels;
}

unsigned int Tone::getNumSamples(){
    return this->numSamples;
}

unsigned int Tone::getSampleRate(){
    return this->sampleRate;
}



double Tone::getDuration(){
    return this->duration;
}

void Tone::setAmplitude(double amplitude){
    this->amplitude = amplitude;
}


