#include "Slider.h"
#include <iostream>

template <typename T>
Slider<T>::Slider()
{

    this->bar.setFillColor(sf::Color::Yellow);
    this->bar.setSize(sf::Vector2f(200, 10));
    this->bar.setPosition(sf::Vector2f(0, 0));

    this->box.setFillColor(sf::Color::Green);
    this->box.setSize(sf::Vector2f(10, 10));
    this->box.setPosition(sf::Vector2f(50, 0));
    this->state = slider_state::SLIDER_IDLE;

    this->maxValue = 100;
    this->minValue = 0;
    this->value = 50;

}

template <typename T>
Slider<T>::~Slider()
{

}

template <typename T>
void Slider<T>::render(sf::RenderTarget *renderer)
{
    renderer->draw(this->bar);
    renderer->draw(this->box);
}

template <typename T>
void Slider<T>::handleEvent(sf::Event &e)
{
    //handle os events
    switch(e.type)
    {
        case sf::Event::MouseButtonPressed:
            if(e.mouseButton.button == sf::Mouse::Left)
                this->_handleMousePress(e);
        break;

        case sf::Event::MouseButtonReleased:
            if(e.mouseButton.button == sf::Mouse::Left)
                this->_handleMouseRelease(e);

        break;

        case sf::Event::MouseMoved:
            this->_handleMouseMove(e);
            
        break;
        
        default:
        break;

    }
}

template <typename T>
void Slider<T>::update()
{
    //not sure what to do here
}

template <typename T>
void Slider<T>::addListener(Listener &l, slider_event event)
{
    //add listener for <event> to list
    this->listeners[event].push_back(l);
}

template <typename T>
void Slider<T>::notify(slider_event event)
{    
    //event triggered, notify listeners
    for(auto it = this->listeners[event].begin(); it != this->listeners[event].end(); it++)
    {
        it->execute();
    }
}

template <typename T>
T Slider<T>::getValue()
{
    return this->value;
}

template <typename T>
T Slider<T>::getMaxValue()
{
    return this->maxValue;
}

template <typename T>
T Slider<T>::getMinValue()
{
    return this->minValue;
}

template <typename T>
void Slider<T>::setValue(T value)
{
    if(value <= this->maxValue && value >= this->minValue){
        this->value = value;

        //calculate 
        double xpos = this->bar.getGlobalBounds().left + (this->bar.getGlobalBounds().width * (value / this->maxValue)); 
        this->box.setPosition(sf::Vector2f(xpos , this->box.getPosition().y));
    }
    else{
        throw new std::invalid_argument("value is out of bounds");
    }
}


template <typename T>
void Slider<T>::_handleMousePress(sf::Event &e)
{
    //trigger event and change state as appropriate
    switch(this->state)
    {
        case slider_state::SLIDER_IDLE:
            //do nothing
            this->state = slider_state::SLIDER_IDLE;
        break;
        case slider_state::SLIDER_HOVERING:
            //go to pressed state notify
            this->notify(slider_event::SLIDER_PRESSED);
            this->state = slider_state::SLIDER_PRESS_ON;
        break;
        case slider_state::SLIDER_PRESS_ON:
            //shouldn't be possible, do nothing
            this->state = slider_state::SLIDER_PRESS_ON;
        break;
        case slider_state::SLIDER_PRESS_OFF:
            //shouldn't be possible, do nothing
            this->state = slider_state::SLIDER_PRESS_OFF;
        break;
    }

}

template <typename T>
void Slider<T>::_handleMouseRelease(sf::Event &e)
{
    //trigger released event and change state

    this->notify(slider_event::SLIDER_RELEASED);

    switch(this->state)
    {
        case slider_state::SLIDER_IDLE:
            //do nothing
            this->state = slider_state::SLIDER_IDLE;
        break;
        case slider_state::SLIDER_HOVERING:
            //do nothing
            this->state = slider_state::SLIDER_HOVERING;
        break;
        case slider_state::SLIDER_PRESS_ON:
            //go to hovering
            this->state = slider_state::SLIDER_HOVERING;
            
            //don't know if I should do this or 
            //just perform whatever needs to be done in released
            //this->notify(slider_event::SLIDER_ENTER);
            
        break;
        case slider_state::SLIDER_PRESS_OFF:
            //go to idle
            this->state = slider_state::SLIDER_IDLE;
        break;
    }    

}

template <typename T>
void Slider<T>::_handleMouseMove(sf::Event &e){
    
    //variable to check if mouse is inside box
    bool inside = false;
   
    if (this->box.getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y)))
    {
        inside = true;
    }
    else 
    {
        inside = false;
    }

    //determine state to change to if applicable
    if (inside)
    {
        switch (this->state)
        {
            case SLIDER_IDLE:
                this->notify(slider_event::SLIDER_ENTER);
                this->state = slider_state::SLIDER_HOVERING;
                break;
            case SLIDER_HOVERING:
                this->state = slider_state::SLIDER_HOVERING;
                break;
            case SLIDER_PRESS_ON:
                this->state = slider_state::SLIDER_PRESS_ON;
                break;
            case SLIDER_PRESS_OFF:
                this->state = slider_state::SLIDER_PRESS_ON;
                break;
        }
    }
    else
    {
        switch (this->state)
        {
            case SLIDER_IDLE:
                this->state = slider_state::SLIDER_IDLE;
                break;
            case SLIDER_HOVERING:
                this->state = slider_state::SLIDER_IDLE;
                this->notify(slider_event::SLIDER_LEFT);
                break;
            case SLIDER_PRESS_ON:
                this->state = slider_state::SLIDER_PRESS_OFF;
                break;
            case SLIDER_PRESS_OFF:
                this->state = slider_state::SLIDER_PRESS_OFF;
                break;
        }
    }

    //slider functionality
    if(this->state == slider_state::SLIDER_PRESS_ON || this->state == slider_state::SLIDER_PRESS_OFF)
    {
     
        if(e.mouseMove.x > this->bar.getGlobalBounds().left && e.mouseMove.x < ( this->bar.getGlobalBounds().left + this->bar.getGlobalBounds().width)){ 
            this->box.setPosition(sf::Vector2f(e.mouseMove.x, this->box.getPosition().y));
        }
        else if(e.mouseMove.x < this->bar.getGlobalBounds().left)
        {
            this->box.setPosition(sf::Vector2f(this->bar.getGlobalBounds().left, this->box.getPosition().y));    
        }
        else if(e.mouseMove.x >= this->bar.getGlobalBounds().left + this->bar.getGlobalBounds().width)
        {
            this->box.setPosition(sf::Vector2f(this->bar.getGlobalBounds().left + this->bar.getGlobalBounds().width - this->box.getSize().x, this->box.getPosition().y));
        }

        //do value calculation based on position
        this->value = (T)(this->maxValue * ( (((double) this->box.getPosition().x - this->bar.getGlobalBounds().left)) / (double) this->bar.getGlobalBounds().width));
    
    }
    else {}
}

void __wrk()
//This function is to force the linker to let me
//Split a template class across two files 
//only numeric types are allowed
{
    Slider<int> t1;
    Slider<float> t2;
    Slider<double> t3;
}