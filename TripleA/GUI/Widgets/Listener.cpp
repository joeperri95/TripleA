#include "Listener.h"

Listener::Listener(){

}

Listener::Listener(std::function<void(void *)> f, void *args){
    this->f = f;
    this->args = args;
}

Listener::~Listener(){

}

void Listener::execute(){
    this->f(this->args);
}