
#include "../../include/Tones/Sine.hpp"

Sine::Sine(unsigned int sampleRate, unsigned int channels, double duration, double amplitude, double freq){

    this->sampleRate = sampleRate;
    this->channels = channels;
    this->duration = duration;
    this->amplitude = amplitude;
    this->numSamples = (unsigned int) duration * sampleRate * channels; 

    this->samples = (short *) malloc(this->numSamples * sizeof(short));
    this->frequency = freq;

    for(unsigned int i = 0; i < this->numSamples; i++){
        short tmp = (short) (this->amplitude * INT16_MAX * sin((double) (this->frequency / this->channels * TWOPI * i) / this->sampleRate));
        this->samples[i] = tmp;
             
    }

}

Sine::~Sine(){
    free(this->samples);
}