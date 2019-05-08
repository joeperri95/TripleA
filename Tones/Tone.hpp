
#ifndef _TONE_H_
#define _TONE_H_

#include <string>
#include "../Effects/Effect.hpp"

#ifndef TWOPI
#define TWOPI 6.283185307
#endif

class Tone{

public:

    Tone();
    ~Tone();

    void applyEffect(Effect &e);
    void setAmplitude(double amplitude);
    
    unsigned int getSampleRate();
    unsigned int getChannels();
    unsigned int getNumSamples();
    double getDuration();
    
    virtual short *getSamples();

protected:

    short *samples;
    unsigned int channels;
    unsigned int sampleRate;
    unsigned int numSamples;
    double duration;
    double amplitude;


}; 

#endif