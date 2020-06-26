#ifndef __CURSOR_H__
#define __CURSOR_H__

#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

class Cursor
//this is a graphical representation of the state of a system
{
public:
    Cursor();
    ~Cursor();

    //main functionality
    void render(sf::RenderTarget *renderer);
    void move(double x, double y);
    void advance(double r);
    void rotateDegrees(double x);
    void rotateRads(double x);

    //setters
    void setPosition(double x, double y);
    void setPosition(sf::Vector2f pos);
    void setFillColour(sf::Color color);
    void setFillColour(uint8_t r, uint8_t g, uint8_t b);
    void setTipColour(sf::Color color);
    void setTipColour(uint8_t r, uint8_t g, uint8_t b);
    void setRotationDegrees(double degrees);
    void setRotationRads(double rads);

    //getters
    double getDegrees();
    double getRadians();
    sf::Vector2f getPosition();

private:
    sf::VertexArray shape;
    sf::VertexArray trail;
    sf::Color backgroundColour;
    sf::Color tipColour;

    int size;
    double angle;
    sf::Vector2f centerPosition;
};

#endif