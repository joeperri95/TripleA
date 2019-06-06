
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

Sine::Sine(Sine &other){
    this->sampleRate = other.getSampleRate();
    this->channels = other.getChannels();
    this->duration = other.getDuration();
    this->amplitude = other.getAmplitude();
    this->numSamples = (unsigned int) this->duration * this->sampleRate * this->channels; 

    this->samples = (short *) malloc(this->numSamples * sizeof(short));
    this->frequency = other.getFrequency();

    for(unsigned int i = 0; i < this->numSamples; i++){
        short tmp = (short) (this->amplitude * INT16_MAX * sin((double) (this->frequency / this->channels * TWOPI * i) / this->sampleRate));
        this->samples[i] = tmp;
             
    }

}

Sine::~Sine(){
    free(this->samples);
}

double Sine::getFrequency(){
    return this->frequency;
}