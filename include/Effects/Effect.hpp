
#ifndef _EFFECT_H_
#define _EFFECT_H_

#ifndef TWOPI
#define TWOPI 6.283185307 
#endif

#include <stdlib.h>
#include <cmath>

class Effect{

public:

    virtual void apply(short *buffer,unsigned int sampleRate, int N){};

private:

    unsigned int sampleRate;


};

#endif