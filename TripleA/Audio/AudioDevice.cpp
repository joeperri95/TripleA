#include "AudioDevice.hpp"
#include <math.h>
#include <iostream>

AudioDevice::AudioDevice(int sampleRate, int channels, int framesPerBuffer)
{
    this->sampleRate = sampleRate;
    this->channels = channels;
    this->framesPerBuffer = framesPerBuffer;
    this->Init();
}

AudioDevice::AudioDevice(int sampleRate, int channels, int framesPerBuffer, Player *player)
{
    this->sampleRate = sampleRate;
    this->channels = channels;
    this->framesPerBuffer = framesPerBuffer;
    this->player = player;
    this->Init();
}
void AudioDevice::Init()
{
    //Configure all options

    std::cout << "Device initializing" << std::endl;

    //build a track with channels
    //build a callback
    Pa_Initialize();
    PaError err = Pa_OpenDefaultStream(&this->stream, 0, this->channels, paInt16, this->sampleRate, this->framesPerBuffer, this->callback, this->player);
    std::cout << Pa_GetErrorText(err) << std::endl;

    Pa_StartStream(this->stream);
}

void AudioDevice::Cleanup()
{
    //Free all memory
    //Close all files

    Pa_CloseStream(this->stream);
    Pa_Terminate();
}

int AudioDevice::callback(
    const void *inputBuffer, void *outputBuffer,
    unsigned long framesPerBuffer,
    const PaStreamCallbackTimeInfo *timeInfo,
    PaStreamCallbackFlags statusFlags,
    void *userData)
{

    Player *player = static_cast<Player *>(userData);
    short *output = (short *)outputBuffer;
    std::vector<short> buffer;

    if (player == nullptr)
    {
        std::cerr << "bwa bwuh" << std::endl;
    }

    if (player->getState() == player_state::PAUSED)
    {
        //maybe stop the stream somehow
        for (int i = 0; i < player->getFramesPerBuffer(); i++)
        {
            for (int j = 0; j < player->getChannels(); j++)
            {
                *(output + i * player->getChannels() + j) = 0;
            }
        }
    }
    else if (player->getState() == player_state::PLAYING)
    {
        buffer = player->getBuffer();
        for (int i = 0; i < player->getFramesPerBuffer(); i++)
        {
            for (int j = 0; j < player->getChannels(); j++)
            {
                *(output + i * player->getChannels() + j) = buffer.at(i * player->getChannels() + j);
            }
        }
    }
    else
    {
        for (int i = 0; i < player->getFramesPerBuffer(); i++)
        {
            for (int j = 0; j < player->getChannels(); j++)
            {
                *(output + i * player->getChannels() + j) = 0;
            }
        }
    }

    return paContinue;
}