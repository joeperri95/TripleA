
//don't use this

#include "SineWave.hpp"

SineWave::SineWave(unsigned int sampleRate, 
                   unsigned int freq, 
                   unsigned int channels, 
                   double duration,
                   double amplitude){
    this->sampleRate = sampleRate;
    this->freq = freq;
    this->channels = channels;
    this->duration = duration;
    this->amplitude = amplitude;

    this->samples = (short*) malloc((int) channels * sampleRate * duration * sizeof(short));

}

SineWave::~SineWave(){
    
    free(this->samples);
    
}

short *SineWave::getSamples(){

    short *copy = (short *) malloc((int) channels * sampleRate * duration * sizeof(short));
    memcpy(copy, this->samples, (int) channels * sampleRate * duration * sizeof(short));
    return copy;
}

void SineWave::generateSineWave()
{       

    for(int i=0; i < ((int) this->channels * this->sampleRate * duration); i++){

        this->samples[i] = (short) (this->amplitude * 65535 * sin( (double) (this->freq * i * 2 * PI) / this->sampleRate ));

    }
    

}

void SineWave::generateSquareWave(int harmonics)
{       
    for(int i=1; i < harmonics; i += 2){
        if(i == 1){
            for(int j=0; j < ((int) this->channels * this->sampleRate * duration); j++){
                this->samples[j] = (short) (this->amplitude * 65535 * sin( (double) (this->freq * j * 2 * PI) / this->sampleRate ));

            }
        }
        else{
            for(int j=0; j < ((int) this->channels * this->sampleRate * duration); j++){
                this->samples[j] = (short) this->samples[j] + ((this->amplitude / i) * 65535 * sin( (double) (this->freq * j * 2 * i * PI) / this->sampleRate ));

            }
        }
    }

}


void SineWave::generateTriangleWave(int harmonics)
{       
    for(int j=0; j < ((int) this->channels * this->sampleRate * duration); j++){
        this->samples[j] = (short) (this->amplitude * 65535 * sin( (double) (this->freq * j * 2 * PI) / this->sampleRate ));
    }

    for(int i=1; i < harmonics; i += 1){
        
        if(i & 0x1){
            for(int j=0; j < ((int) this->channels * this->sampleRate * duration); j++){
                this->samples[j] = (short) this->samples[j] + ((this->amplitude / (i*i)) * 65535 * sin( (double) (this->freq * j * 2 * (2*i + 1) * PI) / this->sampleRate ));

            }
        }
        else{
            for(int j=0; j < ((int) this->channels * this->sampleRate * duration); j++){
                this->samples[j] = (short) this->samples[j] - ((this->amplitude / (i*i)) * 65535 * sin( (double) (this->freq * j * 2 * (2*i + 1) * PI) / this->sampleRate ));
            }
        }
    }

}