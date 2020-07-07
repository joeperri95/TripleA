#ifndef __LISTENER_H__
#define __LISTENER_H__

#include <functional>

class Listener{
/*
    Listeners can be attached to widgets and wrap a function pointer to execute
*/

public:
    Listener();
    Listener(std::function<void(void *)> f, void *args);
    /*
        This can be instantiated easily using a lambda
        Listener l([](void * args)
        {
            //code body using args
        }, args);
    */
    
    ~Listener();

    void execute();


private:
    
    std::function<void(void *)> f;
    void * args;

};

#endif