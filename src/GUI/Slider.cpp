#include "GUI/Slider.hpp"
#include <iostream>

Slider::~Slider(){

}

Slider::Slider(int *value, int maxValue, int minValue, int x, int y, int width, int height){
    this->value = value;
    this->maxValue = maxValue;
    this->minValue = minValue;

    this->barColor = sf::Color(0x0000FFFF);
    this->circleColor = sf::Color(0x777777FF);
    this->sliderBar.setPosition(x,y);
    this->sliderBar.setSize(sf::Vector2f(width, height));
    this->sliderBar.setFillColor(this->barColor);
    this->sliderCircle.setRadius(5);
    this->state = slider_state::SLIDER_IDLE;

    float percent = (float) *(this->value) / this->maxValue;
    int offset = (int) (percent * width) + x - this->sliderCircle.getRadius();
 
    this->sliderCircle.setPosition(sf::Vector2f(offset, y + (height / 2) - this->sliderCircle.getRadius()));
    this->sliderCircle.setFillColor(this->circleColor);

}


void Slider::update(){
    if(this->isPressed() == true){
        this->sliderCircle.setFillColor(sf::Color(0x00FF00FF));
    }
    else if(this->state == slider_state::SLIDER_HOVER){
        this->sliderCircle.setFillColor(sf::Color(0x007700FF));
    }
    else{
        this->sliderCircle.setFillColor(this->circleColor);
    }

}

void Slider::render(sf::RenderTarget *target){
    target->draw(this->sliderBar);
    target->draw(this->sliderCircle);

}

bool Slider::isPressed(){
    if(this->state == slider_state::SLIDER_CLICKED_ON || this->state == slider_state::SLIDER_CLICKED_OFF){
        return true;
    }

    return false;
}

void Slider::setValue(int value){
    if(value > this->maxValue){
        *this->value = this->maxValue;
    }
    else if(value < this->minValue){
        *this->value = this->minValue;
    }
    else{
        *this->value = value;        
    }

    float percent = (float) *(this->value) / this->maxValue;
    int offset = (int) (percent * this->sliderBar.getSize().x) + this->sliderBar.getPosition().x - this->sliderCircle.getRadius();
    
    this->sliderCircle.setPosition( sf::Vector2f(offset, this->sliderBar.getGlobalBounds().top + (this->sliderBar.getGlobalBounds().height / 2) - this->sliderCircle.getRadius()));
}


void Slider::notify(sf::Event e){

    if(e.type == sf::Event::MouseMoved){
        
        switch(this->state){
            case slider_state::SLIDER_IDLE:
                if(this->sliderCircle.getGlobalBounds().contains(e.mouseMove.x, e.mouseMove.y)){
                    this->state = slider_state::SLIDER_HOVER;
                }
                else{
                    this->state = slider_state::SLIDER_IDLE;
                }
                break;
            case slider_state::SLIDER_HOVER:
                if(this->sliderCircle.getGlobalBounds().contains(e.mouseMove.x, e.mouseMove.y)){
                    this->state = slider_state::SLIDER_HOVER;
                }
                else{
                    this->state = slider_state::SLIDER_IDLE;
                }
                break;
            case slider_state::SLIDER_CLICKED_ON:
                if(this->sliderCircle.getGlobalBounds().contains(e.mouseMove.x, e.mouseMove.y)){
                    this->state = slider_state::SLIDER_CLICKED_ON;
                }
                else{
                    this->state = slider_state::SLIDER_CLICKED_OFF;
                }


               
                break;
            case slider_state::SLIDER_CLICKED_OFF:
                if(this->sliderCircle.getGlobalBounds().contains(e.mouseMove.x, e.mouseMove.y)){
                    this->state = slider_state::SLIDER_CLICKED_ON;
                }
                else{
                    this->state = slider_state::SLIDER_CLICKED_ON;
                }
                
                
                break;

        }

        if(this->isPressed()){
            int tempValue = e.mouseMove.x - this->sliderBar.getPosition().x;
            this->setValue(tempValue);

            
        }

    }

    else if(e.type == sf::Event::MouseButtonPressed){
        if(e.mouseButton.button == sf::Mouse::Left){
            switch(this->state){
                case slider_state::SLIDER_IDLE:
                    this->state = slider_state::SLIDER_IDLE;
                    break;
                case slider_state::SLIDER_HOVER:
                    this->state = slider_state::SLIDER_CLICKED_ON;
                    break;
                case slider_state::SLIDER_CLICKED_ON:
                    this->state = slider_state::SLIDER_CLICKED_ON;
                    break;
                case slider_state::SLIDER_CLICKED_OFF:
                    this->state = slider_state::SLIDER_CLICKED_OFF;
                    break;
            }
        }

    }

    else if(e.type == sf::Event::MouseButtonReleased){
        if(e.mouseButton.button == sf::Mouse::Left){
            switch(this->state){
                case slider_state::SLIDER_IDLE:
                    this->state = slider_state::SLIDER_IDLE;
                    break;
                case slider_state::SLIDER_HOVER:
                    this->state = slider_state::SLIDER_HOVER;
                    break;
                case slider_state::SLIDER_CLICKED_ON:
                    this->state = slider_state::SLIDER_HOVER;
                    break;
                case slider_state::SLIDER_CLICKED_OFF:
                    this->state = slider_state::SLIDER_IDLE;
                    break;

            }
        }
    }   

}

int Slider::getMax(){
    return this->maxValue;
}

int Slider::getMin(){
    return this->minValue;
}

int Slider::getValue(){
    return *this->value;
}