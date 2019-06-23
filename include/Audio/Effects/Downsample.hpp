#ifndef __DOWNSAMPLE_H__
#define __DOWNSAMPLE_H__

#include "Effect.hpp"

class Downsample : public Effect{

public:
    
    Downsample(int param);
    ~Downsample();
    void apply(double t, short *sample);

private:
    int param;
    int counter;
    int numTaps;
    short *taps;

};


#endif