#include "../../include/GUI/Knob.hpp"
#include <iostream>

Knob::Knob(int x, int y, int radius){

    this->x = x;
    this->y = y;
    this->radius = radius;

    this->knobCircle.setRadius(radius);
    this->knobCircle.setFillColor(sf::Color::Green);
    this->knobCircle.setOrigin(radius, radius);
    this->knobCircle.setPosition(x, y);
    //this->knobCircle.setPosition(2 * (x + radius), 2 * (y+radius));
    
    

    this->line.setOrigin(radius, 1);
    this->line.setPosition(x,y);
    this->line.setSize(sf::Vector2f(radius, 2.f));
    this->line.setFillColor(sf::Color::Red);
    this->line.rotate(0);


}

Knob::~Knob(){

}

void Knob::render(sf::RenderTarget *target){
    target->draw(this->knobCircle);
    target->draw(this->line);
}

void Knob::update(){


}

void Knob::notify(sf::Event e){

    switch(e.type){
        case sf::Event::MouseMoved:

        break;
        case sf::Event::MouseButtonPressed:

        break;
        case sf::Event::MouseButtonReleased:

        break;
        default:

        break;
    }

}