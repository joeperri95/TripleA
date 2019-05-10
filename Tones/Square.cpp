
#include "Square.hpp"

Square::Square(unsigned int sampleRate, unsigned int channels, double duration, double amplitude, int harmonics, double freq){

    this->sampleRate = sampleRate;
    this->channels = channels;
    this->duration = duration;
    this->amplitude = amplitude;
    this->numSamples = (unsigned int) duration * sampleRate * channels; 

    this->samples = (short *) malloc(this->numSamples * sizeof(short));
    this->frequency = freq;
    this->harmonics = harmonics;

    for(int i=1; i < this->harmonics; i += 2){
        if(i == 1){
            for(int j=0; j < ((int) this->channels * this->sampleRate * duration); j++){
                this->samples[j] = (short) (this->amplitude * 65535 * sin( (double) (this->frequency * j * TWOPI) / this->sampleRate ));

            }
        }
        else{
            for(int j=0; j < ((int) this->channels * this->sampleRate * duration); j++){
                this->samples[j] = (short) this->samples[j] + ((this->amplitude / i) * 65535 * sin( (double) (this->frequency * j * i * TWOPI) / this->sampleRate ));

            }
        }
    }
}

Square::~Square(){
    free(this->samples);
}