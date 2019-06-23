#ifndef __FIR_H__
#define __FIR_H__

#include "Effect.hpp"
#include <string.h>

class FIR : public Effect{

public:
    FIR(int numberOfTaps, double *bValues);
    ~FIR();
    void apply(double t, short *sample);

private:

    int numberOfTaps;
    double *bValues;
    double *taps;

};

#endif