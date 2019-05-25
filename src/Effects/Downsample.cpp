#include "../../include/Effects/Downsample.hpp"

#include <iostream>
#include <random>

Downsample::Downsample(int param){
    this->param = param;
}

void Downsample::apply(short *buffer, unsigned int sampleRate, int N){
    
    int cnt = 0;
    unsigned int temp = buffer[0];
    //unsigned int temp = (short) 128 * (((buffer[0] + (__INT16_MAX__ / 2)) & 0xFF00) >> 8);

    for(int i = 0; i < N; i++){

        /*for(unsigned int j = 0; j < 255; j++){
            if(temp >= (j * 256) && temp < ((j+1) * 256)){
                buffer[i] = j * 256 - (INT16_MAX / 2) ;//+ (std::rand() % 256) ;
            }   
          //  std::cout << buffer[i] << std::endl;
        }
        */
        if(cnt == this->param){
            cnt = 0;
            temp = buffer[i];// (short) 256 * (((buffer[i] + (__INT16_MAX__ / 2)) & 0xFF00) >> 8);
        }

        buffer[i] = temp;        
        cnt++;

        
    
    }
    

}