#ifndef __LISTENER_H__
#define __LISTENER_H__

#include <thread>

class Listener{

public:

    Listener(void (*function)(void *args), void *args);
    ~Listener();

    void execute();
    void executeAsBackgroundThread();

private:

    void (*function)(void *args);
    void *args;

};

#endif