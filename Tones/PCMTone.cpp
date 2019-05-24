
#include "PCMTone.hpp"
#include <memory.h>
#include <fstream>
#include <iostream>

PCMTone::PCMTone(short *samples, unsigned int sampleRate, unsigned int channels, double amplitude, double duration){

    this->channels = channels;
    this->amplitude = amplitude;
    this->sampleRate = sampleRate;
    this->duration = duration;
    this->numSamples =(unsigned int) duration * sampleRate * channels;
    this->samples = (short *) malloc(this->numSamples * sizeof(short));
    memcpy(this->samples, samples, this->numSamples);


}

PCMTone::PCMTone(short *samples, unsigned int sampleRate, unsigned int channels, double amplitude, unsigned int numSamples){
    this->channels = channels;
    this->amplitude = amplitude;
    this->sampleRate = sampleRate;
    this->duration = (double) numSamples / (sampleRate * channels);
    this->numSamples = numSamples;
    this->samples = (short *) malloc(this->numSamples * sizeof(short));
    memcpy(this->samples, samples, this->numSamples);
    
}

PCMTone::PCMTone(std::string fileName){
    std::ifstream fs;

    fs.open(fileName, std::ios::in);

    char _RIFF[5];
    char _FILE_SIZE[5];
    char _WAVE[5];
    char _fmt[5];
    char _fmtLen[5];
    char _fmtType[3];
    char _channels[3];
    char _sampleRate[5];
    char _numBytes[5];
    char _audiofmt[3];
    char _bitspersample[3];
    
    char data[5];
    char fileSize[5];
    char *buff;

    fs.get(_RIFF, 5);
    
    if(std::string("RIFF").compare(_RIFF) != 0){
        std::cerr << "not a valid wav file" << std::endl;
    }
    
    fs.get(_FILE_SIZE, 5);
    fs.get(_WAVE, 5);
    fs.get(_fmt, 5);
    fs.get(_fmtLen, 5);
    fs.get(_fmtType, 3);
    fs.get(_channels, 3);
    fs.get(_sampleRate, 5);
    fs.get(_numBytes, 5);
    fs.get(_audiofmt, 3);
    fs.get(_bitspersample, 3);
    
    fs.get(data, 5);
    fs.get(fileSize, 5);
    buff = (char *) malloc(*(int *)fileSize + 1);
    
    while(std::string("data").compare(data) != 0){

        fs.get(buff, (*(int *) fileSize) + 1);
        fs.get(data, 5);
        fs.get(fileSize, 5);
        
        if(!realloc(buff ,(*(int *) fileSize) + 1)){
            std::cerr << "error allocating bytes";
        }
        
    }

    free(buff);
    
    short *buffer = (short *) malloc((*(int *) fileSize + 1));
    char temp[2];

    for(int i=0; i < (*(int *)fileSize + 1) >> 1; i++){
        fs.read(temp,2);
        buffer[i] = *(short *) temp;
        
    }
    
    this->samples = buffer;
    this->channels = *(short *)_channels;
    this->amplitude = 1.0;
    this->sampleRate = *(unsigned int *) _sampleRate;
    this->numSamples = (*(unsigned int *)fileSize + 1) / 2;
    this->duration = (double) (*(int *)fileSize + 1) / (2 * *(unsigned int *) _sampleRate * *(short *)_channels);

}

PCMTone::~PCMTone(){
    free(this->samples);
}