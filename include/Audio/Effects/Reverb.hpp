#ifndef __REVERB_H__
#define __REVERB_H__

#include "Effect.hpp"

class Reverb : public Effect{

public:
    Reverb(float delayParam, float ampParam);
    void apply(double t, short *sample);

private:
    float delayParam;
    float ampParam;

};

#endif