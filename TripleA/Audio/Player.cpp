#include "Player.hpp"
#include <iostream>

Player::Player(int sampleRate, int channels, int framesPerBuffer)
{
    this->sampleRate = sampleRate;
    this->channels = channels;
    this->framesPerBuffer = framesPerBuffer;

    this->currentSample = 0;
    this->volume = 1.0;
    this->state = player_state::NO_STATE;
    this->currentObject = nullptr;
}

Player::Player(int sampleRate, int channels, int framesPerBuffer, AudioObject *object)
{
    this->sampleRate = sampleRate;
    this->channels = channels;
    this->framesPerBuffer = framesPerBuffer;

    this->currentSample = 0;
    this->state = player_state::NO_STATE;
    this->currentObject = object;
    this->volume = 1.0;
    this->buffer.resize(object->getBuffSize());
}

Player::~Player()
{
}

void Player::Play()
{
    this->state = player_state::PLAYING;
}

void Player::Stop()
{
    this->state = player_state::STOPPED;
}

void Player::Pause()
{
    this->state = player_state::PAUSED;
}

AudioObject *Player::getCurrentObject()
{
    return this->currentObject;
}

int Player::getState()
{
    return this->state;
}

int Player::getSampleRate()
{
    return this->sampleRate;
}

int Player::getChannels()
{
    return this->channels;
}

int Player::getFramesPerBuffer()
{
    return this->framesPerBuffer;
}

void Player::setVolume(float volume)
{
    this->volume = volume;
}

float Player::getVolume()
{
    return this->volume;
}

long Player::getCurrentSample()
{
    return this->currentSample;
}

void Player::setCurrentSample(long sample)
{
    this->currentSample = sample;
}

std::vector<short> Player::getBuffer()
{

    this->buffer = this->currentObject->getSamples(this->currentSample);

    std::vector<short> retval(this->currentObject->getBuffSize());

    for (int i = 0; i < this->buffer.size(); i++)
    {
        retval.at(i) = (short)(this->volume * this->buffer.at(i));
    }

    this->currentSample += this->currentObject->getBuffSize();
    return retval;
}