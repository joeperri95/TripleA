#ifndef __AUDIODEVICE_H__
#define __AUDIODEVICE_H__

#include <portaudio.h>
#include "Player.hpp"

class AudioDevice
{
public:
    AudioDevice(int sampleRate, int channels, int framesPerBuffer);
    AudioDevice(int sampleRate, int channels, int framesPerBuffer, Player *player);

    void Cleanup();
    void Init();

    bool isPlaying();

private:
    int channels;
    int sampleRate;
    int framesPerBuffer;
    PaStream *stream;
    Player *player;

    static int callback(
        const void *inputBuffer, void *outputBuffer,
        unsigned long framesPerBuffer,
        const PaStreamCallbackTimeInfo *timeInfo,
        PaStreamCallbackFlags statusFlags,
        void *userData);
};

#endif