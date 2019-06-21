#include "GUI/DropDownItem.hpp"

#include <iostream>

DropDownItem::~DropDownItem(){

}

DropDownItem::DropDownItem(int width, int height, std::string name){
    this->name = name;
    this->height = height;
    this->width = width;

    this->state = dropdown_state::DROPDOWN_HIDDEN;

    this->rect.setSize(sf::Vector2f(width, height));
    this->rect.setFillColor(sf::Color(sf::Color::Cyan));

    sf::Font f;
    f.loadFromFile("res/fonts/Ubuntu-R.ttf");
    this->text.setFont(f);
    this->text.setString(name);
    this->stateChange = false;
}

DropDownItem::DropDownItem(int height, std::string name){
    this->name = name;

    this->state = dropdown_state::DROPDOWN_HIDDEN;

    this->font.loadFromFile("res/fonts/Ubuntu-R.ttf");
    this->text.setFont(this->font);
    this->text.setString(name);
    this->text.setCharacterSize(10);

    this->width = this->text.getGlobalBounds().width + 10;
    this->height = height;
    this->rect.setSize(sf::Vector2f(this->width, this->height));
    this->rect.setFillColor(sf::Color(sf::Color::Cyan));
    this->stateChange = false;
}

void DropDownItem::addListener(Listener &l){
    this->listeners.push_back(l);
}

void DropDownItem::setSize(int width, int height){
    this->width = width;
    this->height = height;
    this->rect.setSize(sf::Vector2f(width, height));
}

std::string DropDownItem::getName(){
    return this->name;
}

int DropDownItem::getHeight(){
    return this->height;
}

int DropDownItem::getWidth(){
    return this->width;
}

void DropDownItem::setPosition(int x, int y){
    this->x = x;
    this->y = y;
    this->rect.setPosition(x, y);
    this->text.setPosition(x, y + 5);
}

void DropDownItem::update(){
    
    if(this->stateChange){
        this->stateChange = false;
        
        switch(this->state){
            case dropdown_state::DROPDOWN_IDLE:
                this->rect.setFillColor(sf::Color::Cyan);
            break;
            case dropdown_state::DROPDOWN_HOVER:
                this->rect.setFillColor(sf::Color::Magenta);
            break;
            case dropdown_state::DROPDOWN_HIDDEN:

            break;
            case dropdown_state::DROPDOWN_CLICKED_ON:
                this->rect.setFillColor(sf::Color::Yellow);
            break;
            case dropdown_state::DROPDOWN_CLICKED_OFF:
                this->rect.setFillColor(sf::Color::Yellow);
            break;
        }
    }
    if(this->active){
        this->active = false;
        if(this->state != dropdown_state::DROPDOWN_HIDDEN){
            for(auto i = this->listeners.begin(); i != this->listeners.end(); ++i){
                i->execute();
            }
        }
    }
    

}

void DropDownItem::render(sf::RenderTarget *target){
    if(this->state != dropdown_state::DROPDOWN_HIDDEN){
        target->draw(this->rect);
        target->draw(this->text);
    }
}

void DropDownItem::notify(sf::Event e){
    
    bool inside;

    switch(e.type){
        case sf::Event::MouseMoved:
            

            if(this->rect.getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y))){
                inside = true;
            }
            else{
                inside = false;
            }
            
            switch(this->state){
                case dropdown_state::DROPDOWN_IDLE:
                    if(inside){
                        this->state = dropdown_state::DROPDOWN_HOVER;
                        this->stateChange = true;
                    }
                break;
                case dropdown_state::DROPDOWN_HOVER:
                    if(!inside){
                        this->state = dropdown_state::DROPDOWN_IDLE;
                        this->stateChange = true;
                    }
                break;
                case dropdown_state::DROPDOWN_HIDDEN:
                    
                break;
                case dropdown_state::DROPDOWN_CLICKED_ON:
                    if(!inside){
                        this->state = dropdown_state::DROPDOWN_CLICKED_OFF;
                        this->stateChange = true;
                    }
                break;
                case dropdown_state::DROPDOWN_CLICKED_OFF:
                    if(inside){
                        this->state = dropdown_state::DROPDOWN_CLICKED_ON;
                        this->stateChange = true;
                    }
                break;

                default:
                break;
            }
        break;
        case sf::Event::MouseButtonPressed:
            switch(this->state){
                case dropdown_state::DROPDOWN_IDLE:
                    //nothing happens
                break;
                case dropdown_state::DROPDOWN_HOVER:
                    this->state = dropdown_state::DROPDOWN_CLICKED_ON;
                    this->active = true;
                    this->stateChange = true;
                break;
                case dropdown_state::DROPDOWN_HIDDEN:

                break;
                case dropdown_state::DROPDOWN_CLICKED_ON:

                break;
                case dropdown_state::DROPDOWN_CLICKED_OFF:

                break;
            }
        break;
        case sf::Event::MouseButtonReleased:
            switch(this->state){
                case dropdown_state::DROPDOWN_IDLE:
                    
                break;
                case dropdown_state::DROPDOWN_HOVER:
                    
                break;
                case dropdown_state::DROPDOWN_HIDDEN:

                break;
                case dropdown_state::DROPDOWN_CLICKED_ON:
                    this->state = dropdown_state::DROPDOWN_HOVER;
                    this->stateChange = true;
                break;
                case dropdown_state::DROPDOWN_CLICKED_OFF:
                    this->state = dropdown_state::DROPDOWN_IDLE;
                    this->stateChange = true;
                break;
            }
        break;
        default:

        break;
    }
    
    
}   

dropdown_state DropDownItem::getState(){
    return this->state;
}

void DropDownItem::setState(dropdown_state newState){
    this->state = newState;
}
