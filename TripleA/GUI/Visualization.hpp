#ifndef __VISUALIZATION_H__
#define __VISUALIZATION_H__

#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Cursor.hpp"
#include "ApplicationState.h"
#include "MenuState.h"

class Visualization
{
public:
    Visualization(int width, int height);
    ~Visualization();
    //main methods
    void handleEvents();
    void render();
    void setState(ApplicationState *state);
    sf::RenderWindow *getWindowHandle();

    //getters
    bool isOpen();

private:
    //main sfml objects
    sf::RenderWindow *window;
    sf::Event event;

    int width, height;

    //polymorphic state that handles input and what to render
    ApplicationState *state;

    //text related
    sf::Font font;
};

#endif