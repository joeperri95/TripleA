#ifndef __EFFECT_H__
#define __EFFECT_H__

#include <vector>
#include <memory>
#include "AudioObject.hpp"

class Effect
{

public:
    Effect();
    ~Effect();

    virtual std::vector<short> apply(std::vector<short> obj);
};

#endif