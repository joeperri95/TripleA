#include "../../include/GUI/Listener.hpp"

Listener::Listener(void (*function)(void *arg), void *args){
    this->function = function;
    this->args = args;

}

Listener::~Listener(){
    
}

void Listener::execute(){

    (this->function)(this->args);

}

void Listener::executeAsBackgroundThread(){

    std::thread th(this->function, this->args);
    th.detach();

}