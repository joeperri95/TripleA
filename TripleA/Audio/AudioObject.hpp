#ifndef __AUDIOOBJECT_H__
#define __AUDIOOBJECT_H__

#include <vector>

class AudioObject
{

public:
    //get a buffer worth of samples starting at sample t
    virtual std::vector<short> getSamples(unsigned long t) = 0;
    long getBuffSize()
    {
        return this->buffsize;
    }

    long getLength()
    {
        return this->length;
    }

protected:
    unsigned long buffsize; //size of outputbuffer in getsamples
    unsigned long length;   //total buffersize in bytes
    std::vector<short> buffer;
};

#endif