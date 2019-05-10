
#include "Triangle.hpp"

Triangle::Triangle(unsigned int sampleRate, unsigned int channels, double duration, double amplitude, int harmonics, double freq){

    this->sampleRate = sampleRate;
    this->channels = channels;
    this->duration = duration;
    this->amplitude = amplitude;
    this->numSamples = (unsigned int) duration * sampleRate * channels; 

    this->samples = (short *) malloc(this->numSamples * sizeof(short));
    this->frequency = freq;
    this->harmonics = harmonics;

    for(int j=0; j < this->numSamples; j++){
        this->samples[j] = (short) (this->amplitude * INT16_MAX * sin( (double) (this->frequency * j * TWOPI) / this->sampleRate ));
    }

    for(int i=1; i < harmonics; i++){
        
        if(i & 0x1){
            for(unsigned int j=0; j < this->numSamples; j++){
                this->samples[j] = (short) (this->samples[j] + ((this->amplitude / (pow(2*i+1, 2))) * INT16_MAX * sin( (double) (this->frequency * j * (2*i + 1) * TWOPI) / this->sampleRate )));
            }
        }
        else{
            for(unsigned int j=0; j < this->numSamples; j++){
                this->samples[j] = (short) (this->samples[j] - ((this->amplitude / (pow(2*i+1, 2))) * INT16_MAX * sin( (double) (this->frequency * j * (2*i + 1) * TWOPI) / this->sampleRate )));
            }
        }
    }
}

Triangle::~Triangle(){
    free(this->samples);
}