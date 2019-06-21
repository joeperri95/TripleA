
#ifndef _TRACK_H_
#define _TRACK_H_

#include "AudioObject.hpp"
#include "Tone.hpp"
#include <map>

class Track : public AudioObject{

public:

    Track(double length);
    Track();
    ~Track();

    void addTone(int id, Tone *tone);
    void removeTone(int id);
    void setAmplitude(double amp);
    void setLoop(bool loop);
    double getAmplitude();
    void addEffect(Effect *e);

    short callback(double t);
    float getPlaybackPercentage(double t);

private:

    std::map<int, Tone *> tones;
    std::vector<Effect *> effects;
    double length;
    double amplitude;
    bool loop;

};

#endif