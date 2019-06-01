#ifndef __LISTENER_H__
#define __LISTENER_H__

class Listener{

public:

    Listener(void (*function)(void *args), void *args);
    ~Listener();

    void Execute();


private:

    void (*function)(void *args);
    void *args;

};

#endif