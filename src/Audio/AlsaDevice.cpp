#include "../../include/Audio/AlsaDevice.hpp"

//#define DEBUG 0

AlsaDevice::AlsaDevice(){

}

AlsaDevice::~AlsaDevice(){
    
    this->cleanup();

    #ifdef DEBUG
    printf("done at %f\n", this->time);
    #endif

}

AlsaDevice::AlsaDevice(std::string device, 
                    unsigned int rate, 
                    unsigned int channels, 
                    unsigned int periodSize, 
                    unsigned int periods)
{
    this->deviceName = device;
    this->sampleRate = rate;
    this->channels = channels;
    this->periodSize = periodSize;
    this->periods = periods;
    this->bufferSize = periods * periodSize;
    this->handle = NULL;
    this->audio = NULL;

    this->init();

}


AlsaDevice::AlsaDevice(std::string device, 
                    unsigned int rate, 
                    unsigned int channels, 
                    unsigned int periodSize, 
                    unsigned int periods,
                    AudioObject *obj)
{

    this->deviceName = device;
    this->sampleRate = rate;
    this->channels = channels;
    this->periodSize = periodSize;
    this->periods = periods;
    this->bufferSize = periods * periodSize;
    this->handle = NULL;
    this->audio = obj;

    this->init();

}

void AlsaDevice::writeSamples(short *buffer, int N){
    //write N samples from buffer

    short *ptr = buffer;
    int error_code;
    int totalRemaining = N;
    int periodRemaining = this->periodSize;

    while(totalRemaining > 0){
        while(periodRemaining > 0){
            
            error_code = snd_pcm_writei(this->handle, ptr, periodRemaining);
            
            if(error_code == -EPIPE){
                printf("%d buffer underun: %s\n", error_code, snd_strerror(error_code));
                snd_pcm_prepare(this->handle);
            }
            else if(error_code < 0){    
                printf("%d error: %s\n", error_code, snd_strerror(error_code));
            }
            else{
                periodRemaining -= error_code;
                ptr += error_code * this->channels;
            }
        
        }

        periodRemaining = this->periodSize;
        totalRemaining -= this->periodSize;
    }

}

void AlsaDevice::cleanup(){
    //if this is called the AlsaDevice is useless
    //a new one must be created

    if(!this->cleanedUp){
        this->threadActive = false;

        if(this->audioThread.joinable()){
            this->audioThread.join();
        }

        snd_pcm_drain(this->handle);
        snd_pcm_drop(this->handle);
        snd_pcm_hw_free(this->handle);
        snd_pcm_close(this->handle);

        free(this->buffer);
        this->cleanedUp = true;
    }
}

void AlsaDevice::init(){
    
    if(snd_pcm_open(&this->handle, this->deviceName.c_str(), SND_PCM_STREAM_PLAYBACK, 0) < 0){
        exit(EXIT_FAILURE);
    }

    this->setHwParams();
    this->setSwParams();

    snd_pcm_start(this->handle);

    this->time = 0.0;

    this->buffer = (short *) malloc(this->bufferSize * sizeof(short));
    
    std::fill(this->buffer, this->buffer + this->bufferSize, 0);
    this->writeSamples(this->buffer , this->periodSize);
    
    this->cleanedUp = false;
    
    this->threadActive = true;
    this->playing = true;
    this->audioThread = std::thread(&AlsaDevice::threadMain, this); 
    #ifdef DEBUG
    printf("initialized at %f\n", this->time);
    #endif
}


void AlsaDevice::setHwParams(){

    int error_code;

    snd_pcm_hw_params_alloca(&this->hw_params);
    snd_pcm_hw_params_any(this->handle, this->hw_params);
    
    snd_pcm_hw_params_set_format(this->handle, this->hw_params, SND_PCM_FORMAT_S16_LE);
    snd_pcm_hw_params_set_rate(this->handle, this->hw_params, this->sampleRate, 0);
    snd_pcm_hw_params_set_channels(this->handle, this->hw_params, this->channels);
    snd_pcm_hw_params_set_period_time(this->handle, this->hw_params, this->periodSize, 0);
    snd_pcm_hw_params_set_periods(this->handle, this->hw_params, this->periods, 0);
    snd_pcm_hw_params_set_buffer_size(this->handle, this->hw_params, this->periodSize * this->periods);

    error_code = snd_pcm_hw_params(this->handle, this->hw_params);
    
    if(error_code < 0){
        this->cleanup();
    }

}

void AlsaDevice::setSwParams(){

    //might be unnecesary method

    int error_code;

    snd_pcm_sw_params_alloca(&this->sw_params);
    snd_pcm_sw_params_current(this->handle, this->sw_params);
    
    snd_pcm_sw_params_set_start_threshold(this->handle, this->sw_params, this->periodSize * this->periods);
    snd_pcm_sw_params_set_avail_min(this->handle, this->sw_params, this->periodSize);

    snd_pcm_uframes_t boundary;
    snd_pcm_sw_params_get_boundary(this->sw_params, &boundary);

    snd_pcm_sw_params_set_stop_threshold(this->handle, this->sw_params, boundary);
    snd_pcm_sw_params_set_silence_threshold(this->handle, this->sw_params, boundary);

    error_code = snd_pcm_sw_params(this->handle, this->sw_params);
    if(error_code < 0){
        this->cleanup();
    }

}

void AlsaDevice::setChannels(unsigned int channels){

    int error_code;
    error_code = snd_pcm_hw_params_set_channels(this->handle, this->hw_params, channels);
    
    this->channels = channels;

    if(error_code < 0){
        this->cleanup();
    }

}

void AlsaDevice::setSampleRate(unsigned int sampleRate){
    
    int error_code;
    error_code = snd_pcm_hw_params_set_rate(this->handle, this->hw_params, sampleRate, 0);
    
    this->sampleRate = sampleRate;

    if(error_code < 0){
        this->cleanup();
    }

}

/* 

void AlsaDevice::setCallback(short (*f)(double t, void *userData)){
    
    this->time = 0;

    this->pause();
    snd_pcm_drop(this->handle);
    this->callBack = f;
    snd_pcm_prepare(this->handle);
    this->resume();
    
    #ifdef DEBUG
    printf("callback changed\n");
    #endif

}
 

void AlsaDevice::setUserData(void *userData){
    this->currentData = userData;
}

*/

void AlsaDevice::setAudioObject(AudioObject *audio){
    this->audio = audio;
}

void AlsaDevice::threadMain(){

    while(this->threadActive){
        if(this->playing){
            if(this->audio){
                
                for(unsigned int i = 0; i < this->bufferSize; i++){
                    for(unsigned int j = 0; j < this->channels; j++){
                        *(this->buffer + i + j) = this->audio->callback(this->time);
                    }
                    this->time += 1.0 / (this->sampleRate * this->channels);
                }

                this->writeSamples(this->buffer , this->periodSize);
            }

            else{
                std::fill(this->buffer, this->buffer + this->bufferSize, 0);
                this->writeSamples(this->buffer , this->periodSize);
            }     

            #if DEBUG == 1  
            printf("time :%f\n", time);
            #endif
        }
    }

}

void AlsaDevice::pause(){

    if(this->playing){

        snd_pcm_pause(this->handle, 1);
        this->playing = false;
    
    }
    #ifdef DEBUG
    printf("paused at %f\n", this->time);
    #endif

}

void AlsaDevice::resume(){

    if(!this->playing){
        snd_pcm_pause(this->handle, 0);
        this->playing = true;

    }
    #ifdef DEBUG
    printf("resumed at %f\n", this->time);
    #endif
}

void AlsaDevice::stop(){

    this->playing = false;
    this->cleanup();

}

double AlsaDevice::getTime(){
    return this->time;
}