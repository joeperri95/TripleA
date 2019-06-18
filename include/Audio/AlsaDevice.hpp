#ifndef __ALSA_DEVICE_H__
#define __ALSA_DEVICE_H__

#include <alsa/asoundlib.h>
#include <string>
#include <atomic>
#include <thread>

//prefer audioobject to callback and data
#include "AudioObject.hpp"


class AlsaDevice{

public:

    AlsaDevice();
    AlsaDevice(std::string device, 
                    unsigned int rate, 
                    unsigned int channels, 
                    unsigned int periodSize, 
                    unsigned int periods);

    AlsaDevice(std::string device, 
                    unsigned int rate, 
                    unsigned int channels, 
                    unsigned int periodSize, 
                    unsigned int periods,
                    AudioObject *obj);
    
    ~AlsaDevice();

    void setSampleRate(unsigned int rate);
    void setChannels(unsigned int channels);
    
    //void setCallback(short (*f)(double time, void *userData));
    
    void setAudioObject(AudioObject *obj);
    //void setUserData(void *data);

    double getTime();

    void pause();
    void resume();
    void stop();

private:

    std::string deviceName;

    snd_pcm_t *handle;
    snd_pcm_hw_params_t *hw_params;
    snd_pcm_sw_params_t *sw_params;
    unsigned int sampleRate;
    unsigned int channels;
    unsigned int periodSize;
    unsigned int periods;
    unsigned int bufferSize;   
    short *buffer;
    double time;

    void setHwParams();
    void setSwParams();
    void threadMain();
    void init();
    void cleanup();
    void writeSamples(short *samples, int N);
    
    AudioObject *audio;

    std::thread audioThread;
    std::atomic<bool> threadActive;
    std::atomic<bool> playing;
    std::atomic<double> volume;
    bool cleanedUp;

};

#endif