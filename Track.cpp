
#include "Track.hpp"
#include <iostream>

Track::Track(Device &d, unsigned int sampleRate, unsigned int channels){
    this->dev = Device(d);
    this->sampleRate = sampleRate;
    this->numSamples = 0;
    this->buffer = NULL;
    this->channels = channels;
}

Track::Track(unsigned int sampleRate, unsigned int channels){
    //this->dev = Device("default", SND_PCM_FORMAT_S16_LE, sampleRate * channels, 1, 2, 8192, 4096, 0, SND_PCM_ACCESS_RW_INTERLEAVED);
    this->sampleRate = sampleRate;
    this->numSamples = 0;
    this->buffer = NULL;
    this->channels = channels;
}



Track::~Track(){
    free(this->buffer);
}


void Track::addTone(Tone &t, double startTime){

    if(this->buffer == NULL){

        if(t.getSampleRate() != this->sampleRate){
            std::cerr << "unequal sample rates not yet implemented" << std::endl;
            return;
        }

        if(t.getChannels() != this->channels ){
            std::cerr << "unequal channels not yet implemented" << std::endl;
            return;
        }
        

        buffer = (short *) malloc((t.getNumSamples() + (startTime * this->sampleRate * this->channels)) * sizeof(short));
        this->numSamples += t.getNumSamples();
        for(int i = 0; i < startTime * this->sampleRate * this->channels; i++){
            *(buffer + i) = 0;
        }
    }


}


void Track::play(){

    this->dev.writeSamples(this->buffer, this->numSamples);
    
}