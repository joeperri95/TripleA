#include "Tone.hpp"

class PCMTone : public Tone{

public:
    PCMTone(short *samples, unsigned int sampleRate, unsigned int channels, double amplitude, double duration);
    PCMTone(short *samples, unsigned int sampleRate, unsigned int channels, double amplitude, unsigned int numSamples);
    PCMTone(std::string fileName);
    
    ~PCMTone();

};