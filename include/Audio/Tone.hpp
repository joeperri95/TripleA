#ifndef __TONE_H__
#define __TONE_H__

#include "AudioObject.hpp"
#include <vector>
#include "Effects/Effect.hpp"
#include <stdint.h>

#ifndef TWOPI
#define TWOPI 6.283185307
#endif

#ifndef PI
#define PI  3.141592653
#endif

class Tone : public AudioObject{

public:

    Tone();
    virtual ~Tone();

    virtual short callback(double t) = 0;     
    double getAmplitude();
    void setAmplitude(double amp);
    void addEffect(Effect *e);

protected:

    std::vector<Effect *> effects;
    double amplitude;

};

#endif