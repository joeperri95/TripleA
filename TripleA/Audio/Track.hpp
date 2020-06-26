#ifndef __TRACK_H__
#define __TRACK_H__

#include "AudioObject.hpp"
#include <iostream>
#include <memory>

typedef struct ToneWrapper
{

    ToneWrapper(int index, std::shared_ptr<AudioObject> tone, unsigned long startSample, unsigned long length, double volume)
    {
        this->index = index;
        this->startSample = startSample;
        this->length = length;
        this->tone = tone;
        this->length = length;
        this->volume = volume;
    }

    ~ToneWrapper()
    {
    }

    int index;
    unsigned long startSample;
    unsigned long length;
    std::shared_ptr<AudioObject> tone;
    double volume;

} ToneWrapper;

class Track : public AudioObject
{
    /*
        Track is a wrapper for several audio objects
        Track contains start and stop information for each audio object as well as their volume
            

    */

public:
    Track();
    Track(int channels, long framesPerBuffer);
    ~Track();
    std::vector<short> getSamples(unsigned long sample);

    void addEffect();
    void addTone(std::shared_ptr<AudioObject> tone, unsigned long startSample, unsigned long length, double volume);
    void removeTone(int index);

private:
    bool loop;
    int channels;
    int sampleRate;
    std::vector<ToneWrapper *> tones;
    int toneIndex;
};

#endif