
#include "../include/Track.hpp"
#include <iostream>

Track::Track(Device &d, unsigned int sampleRate, unsigned int channels){
    this->dev = Device(d);
    this->sampleRate = sampleRate;
    this->numSamples = 0;
    this->buffer = NULL;
    this->channels = channels;
    this->currentSample = this-> buffer;
    this->currentSampleCount = 0;
    this->loop = false;
    this->playing = false;
    this->amplitude = 1.0;
}

Track::Track(unsigned int sampleRate, unsigned int channels){
    this->dev = Device("default", SND_PCM_FORMAT_S16_LE, sampleRate * channels, 1, 2, 8192, 4096, 0, SND_PCM_ACCESS_RW_INTERLEAVED);
    this->sampleRate = sampleRate;
    this->numSamples = 0;
    this->buffer = NULL;
    this->channels = channels;
    this->currentSampleCount = 0;
    this->currentSample = NULL;
    this->loop = false;
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
          
        this->currentSampleCount += 8192;
        if((this->currentSampleCount + 8192) > this->numSamples){
            if(this->loop){
                this->currentSample = this->buffer + 32;
                this->currentSampleCount = 32;
            }
            else{
                this->pause();
            }
        }
        else{
            this->currentSample += 8192;
        }
        
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
    
    double diff = amp / this->amplitude;
    this->amplitude = amp;

}

void Track::setLoop(bool val){
    this->loop = val;
}