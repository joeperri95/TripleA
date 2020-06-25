
#include "Audio/Track.hpp"
#include <iostream>

Track::Track(double length)
{
    this->length = length;
    this->amplitude = 1.0;
    this->onTime = 0;
    this->offTime = length;
    this->loop = false;

    this->buffSize = 1024;
    this->buffer = (short *)malloc(this->buffSize * sizeof(short));
    this->time = 0;
}

Track::~Track()
{
}

Track::Track()
{
    this->length = 0;
    this->onTime = 0;
    this->offTime = 0;
    this->loop = false;
}

void Track::addTone(int id, Tone *tone)
{
    this->tones.insert(std::pair<int, Tone *>(id, tone));
}

void Track::removeTone(int id)
{
    this->tones.erase(id);
}

short *Track::callback(double t)
{

    double localT = (this->loop) ? fmod(t, this->length) : t;

    if ((localT >= this->onTime) && (localT < this->offTime))
    {

        for (int j = 0; j < this->buffSize; j++)
        {
            for (auto i = this->tones.begin(); i != this->tones.end(); ++i)
            {

                this->buffer[j] += (i->second->callback(localT)[j]);
            }

            for (auto i : this->effects)
            {
                i->apply(localT, (this->buffer + j));
            }

            this->buffer[j] = (short)(this->amplitude * this->buffer[j]);
        }
    }

    return this->buffer;
}

void Track::setAmplitude(double amplitude)
{
    this->amplitude = amplitude;
}

double Track::getAmplitude()
{
    return this->amplitude;
}

float Track::getPlaybackPercentage(double t)
{

    return t / this->offTime > 1 ? 1 : t / this->offTime;
}

void Track::setLoop(bool loop)
{
    this->loop = loop;
}

void Track::addEffect(Effect *e)
{
    this->effects.push_back(e);
}