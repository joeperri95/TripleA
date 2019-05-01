#ifndef _DEVICE_H_
#define _DEVICE_H_

#include <alsa/asoundlib.h>
#include <string>
#include <stdio.h>

class Device{

//Use this later

/*

int snd_pcm_set_params 	( 	snd_pcm_t *  	pcm,
		snd_pcm_format_t  	format,
		snd_pcm_access_t  	access,
		unsigned int  	channels,
		unsigned int  	rate,
		int  	soft_resample,
		unsigned int  	latency 
	) 	

*/




public:

    Device();

    Device(
        std::string _device,
        snd_pcm_format_t _audio_format,
        unsigned int _sample_rate,
        unsigned int _channels,
        int _resample,
        unsigned int _buffer_time,
        unsigned int _period_time,
        int _period_event,
        snd_pcm_access_t _access_type);

    ~Device();

    int set_hw_params(snd_pcm_access_t _access_type);
    int set_sw_params();
    
    int writeSamples(short *samples, int N);

private:
    
    std::string device;
    snd_pcm_format_t audio_format;
    unsigned int channels;
    unsigned int sample_rate;
    int resample;
    int period_event;
    unsigned int buffer_time;
    unsigned int period_time;
    
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *hw_params;
    snd_pcm_sw_params_t *sw_params;
    snd_pcm_sframes_t buffer_size;
    snd_pcm_sframes_t period_size;
    snd_pcm_access_t access_type;
};

#endif