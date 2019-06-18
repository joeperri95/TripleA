
#include "Audio/Effects/Downsample.hpp"

#include <iostream>
#include <random>

Downsample::Downsample(int param){
    this->param = param;
}

void Downsample::apply(double t, short *sample){
    
    //this may not be possible to accomplish in this manner
    //need to look at other samples

}