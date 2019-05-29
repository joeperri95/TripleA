#include "../../include/GUI/Slider.hpp"
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
    

    float percent = (float) *(this->value) / this->maxValue;
    int offset = (int) (percent * width) + x - this->sliderCircle.getRadius();

    this->sliderCircle.setPosition(sf::Vector2f(offset, y + (height / 2) - this->sliderCircle.getRadius()));
    this->sliderCircle.setFillColor(this->circleColor);

}


void Slider::update(sf::Vector2f mousePos){
/*     
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(this->sliderCircle.getGlobalBounds().contains(mousePos)){
            this->pressed = true;
        }
        else{
            if(this->pressed){
                int tempValue = mousePos.x - this->sliderBar.getPosition().x;
                this->setValue(tempValue);
            }
        }

    }
    else{
        this->pressed = false;
    }

    if(this->pressed == true){
        this->sliderCircle.setFillColor(sf::Color(0x00FF00FF));
    }
    else{
        this->sliderCircle.setFillColor(this->circleColor);
    }
 */
}

void Slider::render(sf::RenderTarget *target){
    target->draw(this->sliderBar);
    target->draw(this->sliderCircle);

}

bool Slider::isPressed(){
    return this->pressed;
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
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(this->sliderCircle.getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y))){
                this->pressed = true;
            }
            else{
                if(this->pressed){
                    int tempValue = e.mouseMove.x - this->sliderBar.getPosition().x;
                    this->setValue(tempValue);
                }
            }

        }
        else{
            this->pressed = false;
        }

        if(this->pressed == true){
            this->sliderCircle.setFillColor(sf::Color(0x00FF00FF));
        }
        else{
            this->sliderCircle.setFillColor(this->circleColor);
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