
#include "Audio/Sine.hpp"

Sine::Sine(double onTime,
           double offTime,
           double amplitude,
           double freq)
{

    this->amplitude = amplitude;
    this->frequency = freq;
    this->onTime = onTime;
    this->offTime = offTime;

    //add this in
    this->stepSize = 1.0 / (44100 * 2);
    this->buffSize = 1024;
}

Sine::Sine()
{
    this->onTime = 0.5;
    this->offTime = 1.5;
    this->amplitude = 0.5;
    this->frequency = 440;

    //add this in
    this->stepSize = 1.0 / (44100 * 2);
    this->buffSize = 1024;
}

Sine::~Sine()
{
}

short *Sine::callback(double t)
{

    if ((t >= this->onTime) && (t < this->offTime))
    {

        for (int i = 0; i < this->buffSize; i++)
        {
            this->buffer[i] = (short)(this->amplitude * INT16_MAX * sin((double)(this->frequency * TWOPI * (t + i * this->stepSize))));

            for (auto e : this->effects)
            {
                e->apply(t, (this->buffer + i));
            }
        }
    }

    return this->buffer;
}
