#include "Application.h"

Application::Application(int height, int width) : display(height, width)
{

    this->state = new MenuState("layout.json");    
    this->display.setState(this->state);

    //start thread
    this->updatePeriod = 20;
    this->running = true;
    this->loop = std::unique_ptr<std::thread>(new std::thread(this->_applicationLoop, (void *)this));
}

Application::~Application()
{
    this->loop->join();
}

void Application::update()
//called by internal thread
//update everything every period
{
    this->state->update();
    this->display.render();
    this->display.handleEvents();
    if (!this->display.isOpen() || this->state->isClosing())
    {
        this->running = false;
    }

}

void Application::_applicationLoop(void *args)
//thread that is always running
{
    Application *me = (Application *)args;

    std::chrono::high_resolution_clock clk;
    std::chrono::time_point lastUpdate = clk.now();

    while (me->running)
    {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(clk.now() - lastUpdate).count() > me->updatePeriod)
        {
            lastUpdate = clk.now();
            me->update();
        }
    }
}