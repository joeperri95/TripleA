#ifndef __ENVELOPE_H__
#define __ENVELOPE_H__

#include "Effect.hpp"

class Envelope : public Effect{

public:

    Envelope(
        double attackTime,
        double releaseTime,
        double attackParam,
        double decayParam,
        double releaseParam,
        double attackLevel,
        double sustainLevel
    );

    ~Envelope();

    void apply(double t, short *sample);

private:

    double attackTime;
    double releaseTime;
    double attackParam;
    double decayParam;
    double releaseParam;
    double attackLevel;
    double sustainLevel;

};

#endif