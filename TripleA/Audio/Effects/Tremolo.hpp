#include "Effect.hpp"
#include <cmath>

class Tremolo : public Effect
{

public:
    Tremolo();
    ~Tremolo();

    std::vector<short> apply(std::vector<short> obj);

private:
    double frequency;
    double depth;
};