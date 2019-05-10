
#include "ToneFactory.hpp"

ToneFactory::ToneFactory(){};
ToneFactory::~ToneFactory(){};

Tone ToneFactory::fromWav(std::string filePath){
    
    std::ifstream fs;

    fs.open(filePath, std::ios::in);

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
    buff = (char *) malloc(*(int *)fileSize);

    while(std::string("DATA").compare(data) != 0){
        fs.get(buff, *(int *) fileSize);
        fs.get(data, 5);
        fs.get(fileSize, 5);
        realloc(buff ,*(int *)fileSize);
    }

    free(buff);
    short *buffer = (short *) malloc(*(int *) fileSize * sizeof(short));
    char temp;

    for(int i=0; i < *(int *)fileSize / sizeof(short); i++){
        fs.read(&temp,1);
        buffer[i] = temp << 4;
        fs.read(&temp,1);
        buffer[i] = buffer[i] | temp;
    }

    PCMTone p(buffer, *(unsigned int *) _sampleRate, (unsigned int) *(short *) _channels, 1.0, *(unsigned int *)_numBytes / 2);
    return p;
}