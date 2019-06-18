
#ifndef _EFFECT_H_
#define _EFFECT_H_

#ifndef TWOPI
#define TWOPI 6.283185307 
#endif

#include <stdlib.h>
#include <cmath>

class Effect{

public:

    Effect(){};
    virtual ~Effect(){};

    virtual void apply(double t, short *sample){};
    

};

#endif