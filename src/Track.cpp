
#include "../include/Track.hpp"
#include <iostream>

Track::Track(Device &d, unsigned int sampleRate, unsigned int channels){
    this->dev = Device(d);
    this->sampleRate = sampleRate;
    this->numSamples = 0;
    this->buffer = NULL;
    this->channels = channels;
    this->currentSample = this-> buffer;
    this->playing = false;
    this->amplitude = 1.0;
}

Track::Track(unsigned int sampleRate, unsigned int channels){
    this->dev = Device("default", SND_PCM_FORMAT_S16_LE, sampleRate * channels, 1, 2, 8192, 4096, 0, SND_PCM_ACCESS_RW_INTERLEAVED);
    this->sampleRate = sampleRate;
    this->numSamples = 0;
    this->buffer = NULL;
    this->channels = channels;
    this->playing = false;
    this->amplitude = 1.0;
}



Track::~Track(){

    free(this->buffer);
    
}


void Track::addTone(Tone &t, double startTime){

    if(this->buffer == NULL){

        if(t.getSampleRate() != this->sampleRate){
            //std::cerr << "unequal sample rates not yet implemented" << std::endl;
            //return;
        }

        if(t.getChannels() != this->channels ){
            std::cerr << "unequal channels not yet implemented" << std::endl;
            return;
        }

        int offset = (int) startTime * this->sampleRate * this->channels;   

        this->buffer = (short *) malloc((t.getNumSamples() + offset) * sizeof(short));
        short *tonebuffer = (short *) malloc(t.getNumSamples() * sizeof(short));

        tonebuffer = t.getSamples();

        this->numSamples += t.getNumSamples();
        
        for(int i = 0; i < offset; i++){
            *(this->buffer + i) = 0;
        }
        
        for(unsigned int i = offset; i < t.getNumSamples() + offset; i++){
            *(this->buffer + i) = *(tonebuffer + i);
        }

        //set current sample at start of buffer
        this->currentSample = this->buffer;

    }

    else{
        return;
    }


}

void Track::update(){
    if(this->playing){
        this->dev.writeSamples(this->currentSample, 8192);
        currentSample += 8192;    
    }
}

void Track::pause(){
    this->playing = false;
}

void Track::play(){
    this->playing = true;
    //this->dev.writeSamples(this->buffer, this->numSamples);
    
}

bool Track::isPlaying(){
    return this->playing;
}

void Track::setAmplitude(double amp){
    
    double diff = this->amplitude - amp;
    this->amplitude = amp;

    for(unsigned int i = 0; i < this->numSamples; i++){
    
        *(this->buffer + i) = (1 - diff) * *(this->buffer + i);

    }

}
