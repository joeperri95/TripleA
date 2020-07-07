#ifndef __M_BUTTON_H__
#define __M_BUTTON_H__

#include "IWidget.h"
#include "Listener.h"
#include <iostream>

typedef enum button_state
{
    BUTTON_IDLE,       //mouse is not over button and button is not pressed
    BUTTON_HOVER,      //mouse is over button
    BUTTON_PRESSED_ON, //pressed and mouse is within bounds of defining rectangles
    BUTTON_PRESSED_OFF //pressed and mouse is not within bounds of defining rectangles
} button_state_t;

typedef enum button_event
{
    BUTTON_PRESSED, 
    BUTTON_RELEASED, 
    BUTTON_ENTERED,
    BUTTON_LEFT
} button_event_t;

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
    void setBackgroundColour(sf::Color colour);


    void update();
    void addListener(Listener &listener, button_event event);

protected:
    //button state functionality
    button_state state;    
    std::map<button_event, std::vector<Listener>> listeners;
    void notify(button_event);

    //visualization related
    sf::RectangleShape rect;
    sf::Vector2f size;
    
};

#endif