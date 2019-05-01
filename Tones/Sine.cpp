
#include "Sine.hpp"

Sine::Sine(unsigned int sampleRate, unsigned int channels, double duration, double amplitude, double freq){

    this->sampleRate = sampleRate;
    this->channels = channels;
    this->duration = duration;
    this->amplitude = amplitude;
    this->numSamples = (unsigned int) duration * sampleRate * channels; 

    this->samples = (short *) malloc(this->numSamples * sizeof(short));
    this->frequency = freq;

    for(unsigned int i = 0; i < this->numSamples; i++){
        this->samples[i] = (short) this->amplitude * INT16_MAX * sin((double) (this->frequency * TWOPI * i) / this->sampleRate );
    }
    

}

short *Sine::getSamples(){
    short *copy = (short *) malloc((int) this->channels * this->sampleRate * this->duration * sizeof(short));
    memcpy(copy, this->samples, (int) this->channels * this->sampleRate * this->duration * sizeof(short));
    return copy;

}

Sine::~Sine(){
    free(this->samples);
}