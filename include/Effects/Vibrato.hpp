#ifndef __VIBRATO_H__
#define __VIBRATO_H__

#include "Effect.hpp"

class Vibrato : public Effect {

public:
    Vibrato(double amplitude, double frequency, int modulation);
    Vibrato(double amplitude, double frequency);

    void apply(short *buffer, unsigned int sampleRate, int N);

private:
    double frequency;
    double amplitude;
    //this is the maximum number of samples the Vibrato will stray
    int modulation;
};

#endif