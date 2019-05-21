#ifndef __APP_H__
#define __APP_H__

#include <SFML/Graphics.hpp>
#include "Device.hpp"
#include "Button.hpp"

class App{

public:
    App();
    ~App();

    void init();
    void run();
    void render(); 
    void update();

    void addButton(Button &b);

private:
    sf::RenderWindow *window;
    sf::Event event;
    Device *device;
    std::vector<Button> buttons;

};

#endif