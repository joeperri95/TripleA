#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "AudioObject.hpp"
#include <algorithm>

//I don't know where these should be defined
enum player_state
{
    NO_STATE,
    ERROR,
    PLAYING,
    PAUSED,
    STOPPED
};

/*

might use this later to replace commonly used data

typedef struct audioContext
{
    int sampleRate;
    int channels;
    int framesPerBuffer;

} audioContext;
*/

class Player
{
public:
    Player(int sampleRate, int channels, int framesPerBuffer);
    Player(int sampleRate, int channels, int framesPerBuffer, AudioObject *object);

    ~Player();

    void Play();
    void Pause();
    void Stop();

    void setCurrentObject(AudioObject *object);
    AudioObject *getCurrentObject();

    int getSampleRate();
    int getChannels();
    int getFramesPerBuffer();

    int getState();
    std::vector<short> getBuffer();

    void setVolume(float volume);
    float getVolume();

    void setCurrentSample(long sample);
    long getCurrentSample();

private:
    void update();

    int sampleRate;
    int channels;
    int framesPerBuffer;
    float volume;

    AudioObject *currentObject;
    player_state state;
    long currentSample;
    std::vector<short> buffer;
};

#endif