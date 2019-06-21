#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Widget.hpp"
#include "Listener.hpp"

typedef enum{
    IDLE,
    HOVER,
    PRESSED_ON,
    PRESSED_OFF
}button_state;




class Button : public Widget{

public:

    Button(int x, int y, int width, int height, std::string text);
    Button(int x, int y, int width, int height, std::string text, sf::Font *font);
    Button();
    ~Button();

    void render(sf::RenderTarget *target);
    void update();
    void notify(sf::Event e);
    void addListener(Listener &l);
    void addRect(sf::RectangleShape &r);
    void addRect(int x, int y, int w, int h);


    bool isPressed();
    bool isHovering();

private:

    button_state state;

    bool active;

    std::vector<Listener> listeners;
    std::vector<sf::RectangleShape> rects;
    
    sf::Shape *buttonShape;
    sf::Font *font;
    sf::Text text;

    //may not be necessary
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color clickedColor;

};

#endif