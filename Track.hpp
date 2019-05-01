
#ifndef _TRACK_H_
#define _TRACK_H_

#include "Tone.hpp"
#include "Device.hpp"


class Track{

public:

    Track(Device &d, 
            unsigned int sampleRate,
            unsigned int channels);
    Track(unsigned int sampleRate, unsigned int channels);
    ~Track();

    void addTone(Tone &t, double startTime);
    void play();
    void toWav(std::string filename);
    void toMP3(std::string filename);

private:

    Device dev;
    short *buffer;
    unsigned int sampleRate;
    unsigned long int numSamples;  
    unsigned int channels;

};

#endif