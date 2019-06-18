
#ifndef _TRACK_H_
#define _TRACK_H_

#include "AudioObject.hpp"
#include "Tone.hpp"
#include <vector>

class Track : public AudioObject{

public:

    Track(double length);
    ~Track();

    void addTone(Tone *tone);
    void setAmplitude(double amp);
    double getAmplitude();

    short callback(double t);
    float getPlaybackPercentage(double t);

private:

    std::vector<Tone*> tones;
    double length;
    double amplitude;
};

#endif