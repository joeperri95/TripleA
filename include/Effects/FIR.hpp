#ifndef __FIR_H__
#define __FIR_H__

#include "Effect.hpp"
#include <string.h>

class FIR : public Effect{

public:
    FIR(int numberOfTaps, float *bValues);
    void apply(short *buffer, unsigned int sampleRate, int N);

private:
    int numberOfTaps;
    float *bValues;

};

#endif