#ifndef __VIBRATO_H__
#define __VIBRATO_H__

#include "Effect.hpp"

class Vibrato : public Effect {

public:
    Vibrato(double amplitude, double frequency, int numTaps, int modulation);
    Vibrato(double amplitude, double frequency, int numTaps);
    ~Vibrato();

    void apply(double t, short *sample);

private:

    int numTaps;
    short *taps;

    double frequency;
    double amplitude;
    //this is the maximum number of samples the Vibrato will stray
    int modulation;
};

#endif