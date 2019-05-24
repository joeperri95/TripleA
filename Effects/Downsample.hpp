#ifndef __DOWNSAMPLE_H__
#define __DOWNSAMPLE_H__

#include "Effect.hpp"

class Downsample : public Effect{

public:
    
    Downsample(int param);
    void apply(short *buffer, unsigned int sampleRate, int N);

private:
    int param;

};


#endif