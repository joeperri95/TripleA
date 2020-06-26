#ifndef __AUDIODATA_H__
#define __AUDIODATA_H__

#include "AudioObject.hpp"
#include <string>
#include <fstream>

typedef struct wavData
{
    char _fmt[5];
    char _fmtLen[5];
    char _fmtType[3];
    char _channels[3];
    char _sampleRate[5];
    char _numBytes[5];
    char _audiofmt[3];
    char _bitspersample[3];

} wavData;

class AudioData : public AudioObject
{
public:
    AudioData(std::string filename, long buffsize);
    ~AudioData();
    std::vector<short> getSamples(unsigned long sample);

private:
    void processWavFile(std::string filename);

    //read from wavefile does not have functionality
    wavData metaData;
};

#endif