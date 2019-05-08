
#include "Effect.hpp"

class DecayEffect : public Effect {

public:

    DecayEffect(double decayParam);
    void apply(short *buffer, unsigned int sampleRate, int N);

private:

    double decayParam;

};