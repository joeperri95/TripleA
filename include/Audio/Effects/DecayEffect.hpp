
#include "Effect.hpp"

class DecayEffect : public Effect {

public:

    DecayEffect(double decayParam, double onTime, double offTime);
    void apply(double t, short *sample);

private:

    double onTime;
    double offTime;
    double decayParam;

};