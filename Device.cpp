
#include "Device.hpp"


Device::Device(){}

Device::Device(
    std::string _device,
    snd_pcm_format_t _audio_format,
    unsigned int _sample_rate,
    unsigned int _channels,
    int _resample,
    unsigned int _buffer_time,
    unsigned int _period_time,
    int _period_event,
    snd_pcm_access_t _access_type)
{

    this->sample_rate = _sample_rate;
    this->audio_format = _audio_format;
    this->channels = _channels;
    this->resample = _resample;
    this->buffer_time = _buffer_time;
    this->period_time = _period_time;
    this->device = _device;
    this->period_event = _period_event;
    this->access_type = _access_type;
    
    

    int error_code = snd_pcm_open(&(this->handle), this->device.c_str(), SND_PCM_STREAM_PLAYBACK, 0);
    if(error_code > 0){
        printf("Error opening device %s\n", snd_strerror(error_code));
    }

    error_code = this->set_hw_params();
    if(error_code > 0){
        printf("Error opening device %s\n", snd_strerror(error_code));
    }
    
    error_code = this->set_sw_params();    
    if(error_code > 0){
        printf("Error opening device %s\n", snd_strerror(error_code));
    }

}

Device::~Device(){
	
    int error_code;
	if(this->handle == NULL)
		return;
	if(snd_pcm_state(this->handle) == SND_PCM_STATE_OPEN){
		error_code = snd_pcm_close(this->handle);
				if(error_code < 0)
				printf("error: %s\n", snd_strerror(error_code));
	}
	
}

int Device::set_hw_params(){

    int error_code = 0;
    unsigned int temp_rate;
    int dir;
    snd_pcm_uframes_t size;
    //set up hw params struct
    
    snd_pcm_hw_params_alloca(&this->hw_params);
    error_code = snd_pcm_hw_params_any(this->handle, this->hw_params);
    if (error_code < 0) {
            printf("Broken configuration for playback: no configurations available: %s\n", snd_strerror(error_code));
            return error_code;
    }

    //resampling
    error_code = snd_pcm_hw_params_set_rate_resample(this->handle, this->hw_params, this->resample);
    if (error_code < 0) {
            printf("Resampling setup failed for playback: %s\n", snd_strerror(error_code));
            return error_code;
    }

    //set interleaved read format
    error_code = snd_pcm_hw_params_set_access(this->handle, this->hw_params, this->access_type);
    if (error_code < 0) {
            printf("Access type not available for playback: %s\n", snd_strerror(error_code));
            return error_code;
    }
    //set sample format
    error_code = snd_pcm_hw_params_set_format(this->handle, this->hw_params, this->audio_format);
    if (error_code< 0) {
            printf("Sample format not available for playback: %s\n", snd_strerror(error_code));
            return error_code;
    }
    //set number of channels
    error_code = snd_pcm_hw_params_set_channels(this->handle, this->hw_params, this->channels);
    if (error_code< 0) {
            printf("Channels count (%i) not available for playbacks: %s\n", this->channels, snd_strerror(error_code));
            return error_code;
    }
    
    //set the stream rate
    temp_rate = this->sample_rate;
    //set temporary sample rate to closest available rate
    error_code = snd_pcm_hw_params_set_rate_near(this->handle, this->hw_params, &temp_rate, 0);
    if (error_code< 0) {
            printf("Rate %iHz not available for playback: %s\n", this->sample_rate, snd_strerror(error_code));
            return error_code;
    }
    if (temp_rate != this->sample_rate) {
            printf("Rate doesn't match (requested %iHz, get %iHz)\n", this->sample_rate, error_code);
            return -EINVAL;
    }

    //set the buffer time
    error_code = snd_pcm_hw_params_set_buffer_time_near(this->handle, this->hw_params, &buffer_time, &dir);
    if (error_code< 0) {
            printf("Unable to set buffer time %i for playback: %s\n", buffer_time, snd_strerror(error_code));
            return error_code;
    }
    error_code= snd_pcm_hw_params_get_buffer_size(this->hw_params, &size);
    if (error_code< 0) {
            printf("Unable to get buffer size for playback: %s\n", snd_strerror(error_code));
            return error_code;
    }
    this->buffer_size = size;
    /* set the period time */
    error_code= snd_pcm_hw_params_set_period_time_near(handle, this->hw_params, &period_time, &dir);
    if (error_code< 0) {
            printf("Unable to set period time %i for playback: %s\n", period_time, snd_strerror(error_code));
            return error_code;
    }
    error_code = snd_pcm_hw_params_get_period_size(this->hw_params, &size, &dir);
    if (error_code< 0) {
            printf("Unable to get period size for playback: %s\n", snd_strerror(error_code));
            return error_code;
    }
    this->period_size = size;
    /* write the parameters to device */
    error_code = snd_pcm_hw_params(this->handle, this->hw_params);
    if (error_code< 0) {
            printf("Unable to set hw params for playback: %s\n", snd_strerror(error_code));
            return error_code;
    }

    return error_code;
}

int Device::set_sw_params(){

    int error_code = 0;

    //need to initialize sw params
    snd_pcm_sw_params_alloca(&this->sw_params);

    error_code = snd_pcm_sw_params_current(this->handle, this->sw_params);
    if (error_code < 0) {
            printf("Unable to determine current swparams for playback: %s\n", snd_strerror(error_code));
            return error_code;
    }
    
    /* start the transfer when the buffer is almost full: */
    /* (buffer_size / avail_min) * avail_min */
    error_code = snd_pcm_sw_params_set_start_threshold(this->handle, this->sw_params, (this->buffer_size / this->period_size) * this->period_size);
    if (error_code < 0) {
            printf("Unable to set start threshold mode for playback: %s\n", snd_strerror(error_code));
            return error_code;
    }
    
    /* allow the transfer when at least period_size samples can be processed */
    /* or disable this mechanism when period event is enabled (aka interrupt like style processing) */
    error_code = snd_pcm_sw_params_set_avail_min(this->handle, this->sw_params, this->period_event ? this->buffer_size : this->period_size);
    if (error_code < 0) {
            printf("Unable to set avail min for playback: %s\n", snd_strerror(error_code));
            return error_code;
    }
    /* enable period events when requested */
    if (period_event) {
            error_code = snd_pcm_sw_params_set_period_event(this->handle, this->sw_params, 1);
            if (error_code < 0) {
                    printf("Unable to set period event: %s\n", snd_strerror(error_code));
                    return error_code;
            }
    }
    /* write the parameters to the playback device */
    error_code = snd_pcm_sw_params(this->handle, this->sw_params);
    if (error_code < 0) {
            printf("Unable to set sw params for playback: %s\n", snd_strerror(error_code));
            return error_code;
    }

    return error_code;
}

int Device::writeSamples(short *samples, int N){
    //currently only supports 16bit signed int samples

    int a, b;
    int error_code = 0;
    short* ptr = samples;
    
    a = this->period_size;
    b = N;

    ptr = samples;
    while(b > 0){
        while(a > 0){
            error_code = snd_pcm_writei(this->handle ,ptr, a);
            
            if(error_code < 0){
                printf("%d buffer underun: %s\n", error_code, snd_strerror(error_code));
                snd_pcm_prepare(this->handle);
            }
            else{

                ptr += error_code;
                a -= error_code;
            }
        }
        b -= this->period_size;
        a = this->period_size;
        
    }

    return 0;
}