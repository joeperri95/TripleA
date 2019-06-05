#ifndef __TREMOLO_H__
#define __TREMOLO_H__

#include "Effect.hpp"

class Tremolo : public Effect {

public:
    Tremolo(double amplitude, double frequency);
    void apply(short *buffer, unsigned int sampleRate, int N);

private:
    double amplitude;
    double frequency;

};

#endif