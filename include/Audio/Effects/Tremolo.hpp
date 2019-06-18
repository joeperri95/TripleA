#ifndef __TREMOLO_H__
#define __TREMOLO_H__

#include "Effect.hpp"

class Tremolo : public Effect {

public:
    Tremolo(double amplitude, double frequency);
    void apply(double t, short *sample);

private:
    double amplitude;
    double frequency;

};

#endif