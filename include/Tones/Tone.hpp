
#ifndef _TONE_H_
#define _TONE_H_

#include <string>
#include <stdlib.h>
#include "../Effects/Effect.hpp"

#ifndef TWOPI
#define TWOPI 6.283185307
#endif

#ifndef PI
#define PI  3.141592653
#endif

class Tone{

public:

    Tone();
    Tone(Tone &t);
    ~Tone();

    void applyEffect(Effect &e);
    void setAmplitude(double amplitude);
    
    unsigned int getSampleRate();
    unsigned int getChannels();
    unsigned int getNumSamples();
    double getDuration();
    double getAmplitude();

    short *getSamples();
    short *getNSamples(int start, int n);

protected:

    short *samples;
    unsigned int channels;
    unsigned int sampleRate;
    unsigned int numSamples;
    double duration;
    double amplitude;


}; 

#endif