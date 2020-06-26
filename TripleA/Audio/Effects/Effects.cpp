#include "Effects/Tremolo.hpp"

Tremolo::Tremolo()
{
}

Tremolo::~Tremolo()
{
}

std::vector<short> Tremolo::apply(std::vector<short> obj)
{

    std::vector<short> ret(obj.size());

    for (int i = 0; i < obj.size(); i++)
    {
        ret.at(i) = this->depth * sin(2 * M_PI * i * this->frequency / SAMPLE_RATE) * obj.at(i);
    }
}