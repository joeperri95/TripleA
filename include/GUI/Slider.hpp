#ifndef __SLIDER_H__
#define __SLIDER_H__

#include "Widget.hpp"

class Slider : public Widget{

public:
    Slider();
    Slider(int *value, int maxValue, int minValue, int x, int y, int width, int height);
    ~Slider();

    int getValue();
    int getMin();
    int getMax();

    void render(sf::RenderTarget *target);
    void update(sf::Vector2f mousePos);
    void notify(sf::Event e);
    bool isPressed();
    
    void setValue(int value);
    

private:
    int *value;
    int maxValue;
    int minValue;
    bool pressed;

    sf::Color barColor;
    sf::Color circleColor;
    sf::RectangleShape sliderBar;
    sf::CircleShape sliderCircle;

};

#endif