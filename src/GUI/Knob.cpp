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
    this->state = knob_state::KNOB_IDLE;

}

Knob::~Knob(){

}

void Knob::render(sf::RenderTarget *target){
    target->draw(this->knobCircle);
    target->draw(this->line);
}

void Knob::update(){

    switch(this->state){
        case knob_state::KNOB_IDLE:
            this->knobCircle.setFillColor(sf::Color::Green);
        break;
        case knob_state::KNOB_HOVER:
            this->knobCircle.setFillColor(sf::Color::Yellow);
        break;
        case knob_state::KNOB_CLICKED_ON:
            this->knobCircle.setFillColor(sf::Color::Blue);
        break;
        case knob_state::KNOB_CLICKED_OFF:
            this->knobCircle.setFillColor(sf::Color::Blue);
        break;
    }


}

void Knob::notify(sf::Event e){

    switch(e.type){
        case sf::Event::MouseMoved:
            switch(this->state){
                case knob_state::KNOB_IDLE:
                    if(this->knobCircle.getGlobalBounds().contains(e.mouseMove.x, e.mouseMove.y)){
                        this->state = knob_state::KNOB_HOVER;
                        
                    }
                break;
                case knob_state::KNOB_HOVER:
                    if(!this->knobCircle.getGlobalBounds().contains(e.mouseMove.x, e.mouseMove.y)){
                        this->state = knob_state::KNOB_IDLE;   
                    }
                break;
                case knob_state::KNOB_CLICKED_ON:
                    if(!this->knobCircle.getGlobalBounds().contains(e.mouseMove.x, e.mouseMove.y)){
                        this->state = knob_state::KNOB_CLICKED_OFF;   
                    }
                break;
                case knob_state::KNOB_CLICKED_OFF:
                    if(this->knobCircle.getGlobalBounds().contains(e.mouseMove.x, e.mouseMove.y)){
                        this->state = knob_state::KNOB_CLICKED_ON;   
                    }
                break;

            }
        break;
        case sf::Event::MouseButtonPressed:
            if(e.mouseButton.button == sf::Mouse::Left){
                switch(this->state){             
                    case knob_state::KNOB_IDLE:
                        
                    break;
                    case knob_state::KNOB_HOVER:
                        this->state = knob_state::KNOB_CLICKED_ON;
                    break;
                    case knob_state::KNOB_CLICKED_ON:
                        
                    break;
                    case knob_state::KNOB_CLICKED_OFF:
                    break;

                }
            }
        break;
        case sf::Event::MouseButtonReleased:
            if(e.mouseButton.button == sf::Mouse::Left){
                switch(this->state){
                    case knob_state::KNOB_IDLE:
                    break;
                    case knob_state::KNOB_HOVER:
                    break;
                    case knob_state::KNOB_CLICKED_ON:
                        this->state = knob_state::KNOB_HOVER;
                    break;
                    case knob_state::KNOB_CLICKED_OFF:
                        this->state = knob_state::KNOB_IDLE;
                    break;
                }
            }
        break;
        default:

        break;
    }

}