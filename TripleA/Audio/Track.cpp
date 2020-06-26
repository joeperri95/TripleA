#include "Track.hpp"

Track::Track()
{
    this->buffsize = 0;
    this->loop = false;
    this->channels = 0;
    this->length = 0;
    this->toneIndex = 0;
}

Track::Track(int channels, long framesPerBuffer)
{
    this->buffsize = framesPerBuffer * channels;
    this->loop = false;
    this->channels = channels;
    this->length = 0;
    this->toneIndex = 0;
}

Track::~Track()
{
}

void Track::addTone(std::shared_ptr<AudioObject> tone, unsigned long startSample, unsigned long length, double volume)
{

    ToneWrapper *t = new ToneWrapper(this->toneIndex++, tone, startSample, length, volume);
    this->tones.push_back(t);

    std::cout << t->index << std::endl;
}

void Track::removeTone(int index)
{
 
    for(auto it = this->tones.begin(); it != this->tones.end(); it++)
    {
        if((*it)->index == index)
        {
            this->tones.erase(it);
            std::cout << "tone " << index <<" erased" << std::endl;
            return;
        }
    }
 
}

std::vector<short> Track::getSamples(unsigned long sample)
{
    //sample is the current sample within the track not the audio objects

    std::vector<short> retVal(this->buffsize);

    for (auto currentTone = this->tones.begin(); currentTone != this->tones.end(); currentTone++)
    {

        //check if tone should be played
        if (sample > (*currentTone)->startSample && sample < ((*currentTone)->startSample + (*currentTone)->length))
        {
            std::vector<short> temp = (*currentTone)->tone->getSamples(sample - (*currentTone)->startSample);
            for (int i = 0; i < this->buffsize; i++)
            {
                retVal.at(i) += (*currentTone)->volume * temp.at(i);
            }
        }
    }

    return retVal;
}