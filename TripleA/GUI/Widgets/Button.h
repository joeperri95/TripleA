#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "IWidget.h"
#include <iostream>

typedef enum button_state
{
    IDLE,       //mouse is not over button and button is not pressed
    HOVER,      //mouse is over button
    PRESSED_ON, //pressed and mouse is within bounds of defining rectangles
    PRESSED_OFF //pressed and mouse is not within bounds of defining rectangles
} button_state_t;

class Button : public IWidget
{

public:
    Button();
    ~Button();

    void render(sf::RenderTarget *renderer);
    void handleEvent(sf::Event &e);
    void setPosition(sf::Vector2f newPosition);
    void setSize(int width, int height);
    void setSize(sf::Vector2f newSize);

    void update();

    sf::Color idleColor;

protected:
    //button state functionality
    button_state state;
    bool active; //if button is clicked and released

    //visualization related
    sf::RectangleShape rect;
    sf::Vector2f size;
};

#endif