#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include <chrono>
#include <thread>
#include "ApplicationState.h"
#include "MenuState.h"
#include "Visualization.hpp"
#include "Widgets/Widgets.h"
#include <SFML/System.hpp>

class Application
//This is the top level application
{

public:
    Application(int height, int width);
    ~Application();

    void start();
    void update();

private:
    //display related
    Visualization display;

    //application state
    ApplicationState *state;
    bool running;

    //timekeeping
    std::chrono::high_resolution_clock clock;
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point last_update;
    int updatePeriod; //ms

    //internal thread
    std::unique_ptr<std::thread> loop;
    static void _applicationLoop(void *args);
};

#endif