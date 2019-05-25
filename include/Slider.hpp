#ifndef __SLIDER_H__
#define __SLIDER_H__

#include <SFML/Graphics.hpp>

class Slider{

public:
    Slider();
    Slider(int *value, int maxValue, int minValue, int x, int y, int width, int height);
    ~Slider();

    int getValue();
    void render(sf::RenderTarget *target);
    void update(sf::Vector2f mousePos);
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