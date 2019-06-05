
#include "../../include/Tones/Tone.hpp"

Tone::Tone(){

}

Tone::Tone(Tone &t){
    this->channels = t.getChannels();
    this->numSamples = t.getNumSamples();
    this->sampleRate = t.getSampleRate();
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

short *Tone::getSamples(){
    return this->samples;
}

short *Tone::getNSamples(int start, int n){
    if(n > this->numSamples){
        return NULL;
    }
}

double Tone::getDuration(){
    return this->duration;
}

void Tone::setAmplitude(double amplitude){

    for(unsigned int i = 0; i < this->numSamples; i++){
        this->samples[i] = (short) ( (amplitude / this->amplitude) * this->samples[i]);
    }
    
    this->amplitude = amplitude;
}

void Tone::applyEffect(Effect &e){
    e.apply(this->samples, this->sampleRate, this->numSamples);
}
