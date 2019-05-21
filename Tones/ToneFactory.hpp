
#include "Tone.hpp"
#include <string>
#include <fstream>
#include <iostream>

class ToneFactory{

public:
    ToneFactory();
    ~ToneFactory();

    Tone fromWav(std::string filePath);
    Tone fromWav(char* filePath);
    Tone sineWave(double duration, unsigned int channels, unsigned int sampleRate);
    Tone triangleWave(int harmonics, double duration, unsigned int channels, unsigned int sampleRate);
    Tone squareWave(int harmonics, double duration, unsigned int channels, unsigned int sampleRate);

};