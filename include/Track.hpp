
#ifndef _TRACK_H_
#define _TRACK_H_

#include "Tones/Tone.hpp"
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
    void pause();
    void setAmplitude(double amp);

    void update();
    void toWav(std::string filename);
    void toMP3(std::string filename);

    bool isPlaying();
    float getPlaybackPercentage();

private:

    Device dev;
    short *buffer;
    short *currentSample;
    int currentSampleCount;
    bool playing;
    unsigned int sampleRate;
    unsigned long int numSamples;  
    unsigned int channels;
    double amplitude;

};

#endif