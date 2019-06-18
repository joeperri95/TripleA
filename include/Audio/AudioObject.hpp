#ifndef __AUDIO_OBJECT_H__
#define __AUDIO_OBJECT_H__

class AudioObject {

public:

    AudioObject(){};
    virtual ~AudioObject(){};
    virtual short callback(double t) {};

    double getOnTime(){return this->onTime;};
    double getOffTime(){return this->offTime;};

protected:

    double onTime;
    double offTime;

};

#endif