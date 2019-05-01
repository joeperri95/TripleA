
//don't use this only for reference

#include <math.h>
#include <vector>
#include <alsa/asoundlib.h>

#ifndef PI
#define PI 3.14159265358979323846 
#endif

class SineWave{

public:
    SineWave(
        unsigned int sampleRate, 
        unsigned int freq,
        unsigned int channels,
        double duration,
        double amplitude
    );
    ~SineWave();

    void generateSineWave();
    void generateSquareWave(int harmonics);
    void generateTriangleWave(int harmonics);
    short *getSamples();

private:
    unsigned int sampleRate;
    unsigned int freq;
    unsigned int channels;
    double duration;
    double amplitude;
    short* samples;

    

};
