#ifndef __VIBRATO_H__
#define __VIBRATO_H__

#include "Effect.hpp"

class Vibrato : public Effect {

public:
    Vibrato(unsigned int frequency);
    ~Vibrato();

    void apply(short *buffer, unsigned int sampleRate, int N);

private:
    unsigned int frequency;

};

#endif