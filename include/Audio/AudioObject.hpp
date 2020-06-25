#ifndef __AUDIO_OBJECT_H__
#define __AUDIO_OBJECT_H__

class AudioObject
{

public:
    AudioObject(){};
    virtual ~AudioObject(){};
    virtual short *callback(double t) = 0;

    double getOnTime() { return this->onTime; };
    double getOffTime() { return this->offTime; };
    void setOnTime(double d) { this->onTime = d; };
    void setOffTime(double d) { this->offTime = d; };

protected:
    double onTime;
    double offTime;

    double stepSize;
    int buffSize;
    short *buffer;
};

#endif