#include "../../include/Tones/Sawtooth.hpp"


Sawtooth::Sawtooth(unsigned int sampleRate, unsigned int channels, double duration, double amplitude, int harmonics, double freq){

    this->sampleRate = sampleRate;
    this->channels = channels;
    this->duration = duration;
    this->amplitude = amplitude;
    this->numSamples = (unsigned int) duration * sampleRate * channels; 

    this->samples = (short *) malloc(this->numSamples * sizeof(short));
    this->frequency = freq;
    this->harmonics = harmonics;

    memset(this->samples, 0, this->numSamples);
    
    for(int i=1; i < harmonics; i++){
        
        if(i & 0x1){
            for(unsigned int j=0; j < this->numSamples; j++){
                this->samples[j] = (short) (this->samples[j] + ((this->amplitude / (PI * i) * INT16_MAX * sin( (double) (this->frequency / this->channels * j * i * TWOPI) / this->sampleRate ))));
            }
        }
        else{
            for(unsigned int j=0; j < this->numSamples; j++){
                this->samples[j] = (short) (this->samples[j] - ((this->amplitude / (PI * i) * INT16_MAX * sin( (double) (this->frequency / this->channels * j * i * TWOPI) / this->sampleRate ))));
            }
        }
    }

}

Sawtooth::~Sawtooth(){
    free(this->samples);
}