#include "AudioData.hpp"
#include <iostream>
#include <cmath>

AudioData::AudioData(std::string filename, long buffsize)
{
    this->buffsize = buffsize;
    this->processWavFile(filename);
}

AudioData::~AudioData()
{
}

void AudioData::processWavFile(std::string filename)
{
    std::ifstream fs;

    std::cout << "starting to read " << filename << std::endl;

    char _RIFF[5];
    char _FILE_SIZE[5];
    char _WAVE[5];

    fs.open(filename, std::ios::in);

    //WAV file must start with 'RIFF'
    fs.get(_RIFF, 5);
    if (std::string("RIFF").compare(_RIFF) != 0)
    {
        std::cerr << "not a valid wave file" << std::endl;
    }

    fs.get(_FILE_SIZE, 5); //total file size including header, useless
    fs.get(_WAVE, 5);

    //start of header must be 'WAVE'
    if (std::string("WAVE").compare(_WAVE) != 0)
    {
        std::cerr << "not a valid wave file" << std::endl;
    }

    //read header data
    fs.get(this->metaData._fmt, 5);
    fs.get(this->metaData._fmtLen, 5);
    fs.get(this->metaData._fmtType, 3);
    fs.get(this->metaData._channels, 3);
    fs.get(this->metaData._sampleRate, 5);
    fs.get(this->metaData._numBytes, 5);
    fs.get(this->metaData._audiofmt, 3);
    fs.get(this->metaData._bitspersample, 3);

    char _data[5];
    char _fileSize[5];

    fs.get(_data, 5);
    fs.get(_fileSize, 5);

    //look for 'data' section there may be other sections we don't care about
    while (std::string("data").compare(_data) != 0)
    {
        fs.ignore(*(int *)_fileSize);
        fs.get(_data, 5);
        fs.get(_fileSize, 5);
    }

    this->length = *(int *)_fileSize + 1;
    this->buffer.resize(this->length); //already takes into account size

    char temp[2];

    //only handle the case the data is a 16 bit int for now
    //TODO implement other data types
    std::cout << this->length << std::endl;

    for (int i = 0; i < (this->length >> 1); i++)
    {
        fs.read(temp, 2);
        this->buffer[i] = *(short *)temp;
        //std::cout << this->buffer[i] << ' ' << temp << std::endl;
    }

    std::cout << "done" << std::endl;
    fs.close();
}

std::vector<short> AudioData::getSamples(unsigned long sample)
{

    std::vector<short> retval(this->buffsize);

    if (sample > this->length)
    {
        //outside valid range
        return retval;
    }
    else if ((sample + this->buffsize) > this->length)
    {
        //less than one buffer can be obtained
        for (int i = 0; i < this->buffsize; i++)
        {
            if (i < this->length - sample)
            {
                retval.at(i) = this->buffer.at(sample + i);
            }
            else
            {
                retval.at(i) = 0;
            }
        }

        return retval;
    }

    else
    {

        for (int i = 0; i < this->buffsize; i++)
        {
            retval.at(i) = this->buffer.at(sample + i);
        }

        return retval;
    }
}