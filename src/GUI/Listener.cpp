#include "../../include/GUI/Listener.hpp"

Listener::Listener(void (*function)(void *arg), void *args){
    this->function = function;
    this->args = args;

}

Listener::~Listener(){
    
}

void Listener::Execute(){

    (this->function)(this->args);

}