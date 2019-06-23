#ifndef __DECIMATE_H__
#define __DECIMATE_H__

#include "Effect.hpp"
#include <vector>
#include <stdint.h>

class Decimate : public Effect{

public:
    Decimate(int factor);
    ~Decimate();

    void apply(double t, short *sample);


private:
    int factor;

};


#endif