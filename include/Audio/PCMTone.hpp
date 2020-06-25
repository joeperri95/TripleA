#ifndef __PCM_H__
#define __PCM_H__

#include "Tone.hpp"
#include <string>

class PCMTone : public Tone
{

public:
    PCMTone(short *samples, unsigned int sampleRate, unsigned int channels, double onTime, double offTime);
    PCMTone(short *samples, unsigned int sampleRate, unsigned int channels, double ontTime, unsigned int numSamples);
    PCMTone(std::string fileName, double onTime, double offTime);

    ~PCMTone();

    short *callback(double t);

private:
    unsigned int sampleRate;
    unsigned int channels;
    short *samples;
    int numSamples;
    double duration;
};

#endif