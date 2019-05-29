#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>


typedef enum{
    IDLE,
    HOVER,
    PRESSED_ON,
    PRESSED_OFF
}button_state;


class Button{

public:

    Button(float x, float y, float width, float height, std::string text, sf::Font *font);
    ~Button();

    void render(sf::RenderTarget *target);
    void update(sf::Vector2f mousePos);
    void notify(sf::Event e);

    bool isPressed();
    bool isHovering();
    

private:

    button_state state;

    sf::RectangleShape rect;
    sf::Font *font;
    sf::Text text;

    //may not be necessary
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color clickedColor;

};

#endif