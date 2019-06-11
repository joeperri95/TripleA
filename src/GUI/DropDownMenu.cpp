#include "../../include/GUI/DropDownMenu.hpp"

#include <iostream>

DropDownMenu::DropDownMenu(int height, std::string name){
    this->buttonHeight = height;
    this->name = name;
    this->state = dropdown_state::DROPDOWN_IDLE;
    
    if(!this->font.loadFromFile("res/fonts/Ubuntu-R.ttf")){
        std::cout << "an error has occured throw error" << std::endl;
    }

    this->text.setFont(this->font);
    this->text.setString(name);
    this->text.setCharacterSize(10);

    this->buttonWidth = this->text.getGlobalBounds().width + 10;

    this->numberOfItems = 0;
    this->rect.setSize(sf::Vector2f(this->buttonWidth, height));
    this->rect.setFillColor(sf::Color(0xFF7070FF));
    this->boxHeight = this->buttonHeight;
    this->boxWidth = 0;

}

DropDownMenu::~DropDownMenu(){

}

DropDownMenu::DropDownMenu(int height, int width, std::string name){
    this->buttonHeight = height;
    this->buttonWidth = width;
    this->name = name;
    this->state = dropdown_state::DROPDOWN_IDLE;
    
    if(!this->font.loadFromFile("res/fonts/Ubuntu-R.ttf")){
        std::cout << "an error has occured throw error" << std::endl;
    }

    this->text.setFont(this->font);
    this->text.setString(name);
    this->text.setCharacterSize(10);

    this->numberOfItems = 0;
    this->rect.setSize(sf::Vector2f(height, width));
    this->rect.setFillColor(sf::Color(0xFF7070FF));
    this->boxHeight = this->buttonHeight;
    this->boxWidth = 0;

}

std::string DropDownMenu::getName(){
    return this->name;
}

void DropDownMenu::addItem(DropDownItem &item){
    this->numberOfItems++;

    this->boxHeight += item.getHeight();
    item.setPosition(this->x, this->y + this->boxHeight);
    
    //one width per submenu 
    if(item.getWidth() > this->boxWidth){
        this->boxWidth = item.getWidth();
        for(auto i = this->items.begin(); i != this->items.end(); ++i){
            i->second.setSize(this->boxWidth, i->second.getHeight());
        }
    }

    this->items.insert(std::pair<std::string, DropDownItem>(item.getName(), item));
}

void DropDownMenu::addItem(std::string text){
    DropDownItem item(text, this->buttonHeight);
    this->numberOfItems++;

    this->boxHeight += item.getHeight();
    item.setPosition(this->x, this->y + this->boxHeight);
    
    //one width per submenu 
    if(item.getWidth() > this->boxWidth){
        this->boxWidth = item.getWidth();
        for(auto i = this->items.begin(); i != this->items.end(); ++i){
            i->second.setSize(this->boxWidth, i->second.getHeight());
        }
    }

    this->items.insert(std::pair<std::string, DropDownItem>(item.getName(), item));
}

sf::RectangleShape DropDownMenu::getRect(){
    return this->rect;
}

void DropDownMenu::setPosition(int x, int y){
    this->x = x;
    this->y = y;
    this->rect.setPosition(x,y);
    this->text.setPosition(x + 5,y + 5);
}

void DropDownMenu::update(){
    switch(this->state){
        case dropdown_state::DROPDOWN_IDLE:
            this->rect.setFillColor(sf::Color(0xFF7070FF));
        break;
        case dropdown_state::DROPDOWN_HOVER:
            this->rect.setFillColor(sf::Color::Blue);
        break;
        case dropdown_state::DROPDOWN_HIDDEN:

        break;
        case dropdown_state::DROPDOWN_CLICKED_ON:
            this->rect.setFillColor(sf::Color(0xCF6060FF));
            this->rect.setOutlineColor(sf::Color::Black);
            this->rect.setOutlineThickness(1);
        break;
        case dropdown_state::DROPDOWN_CLICKED_OFF:
            this->rect.setFillColor(sf::Color(0xCF6060FF));
            this->rect.setOutlineColor(sf::Color::Black);
            this->rect.setOutlineThickness(1);
        break;

    }

    for(auto i = this->items.begin(); i != this->items.end(); ++i){
        i->second.update();
    }

}

void DropDownMenu::render(sf::RenderTarget *target){

    target->draw(this->rect);
    target->draw(this->text);

    for(auto i = this->items.begin(); i != this->items.end(); ++i){
        i->second.render(target);
    }


}

dropdown_state DropDownMenu::getState(){
    return this->state;
}

void DropDownMenu::setState(dropdown_state newState){
    this->state = newState;
}

void DropDownMenu::notify(sf::Event e){
    switch(e.type){
        case sf::Event::MouseMoved:
            if(this->rect.getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y))){
                switch(this->state){
                    case dropdown_state::DROPDOWN_IDLE:
                        this->state = dropdown_state::DROPDOWN_HOVER;
                    break;
                    case dropdown_state::DROPDOWN_HOVER:
                        //nothing happens
                    break;
                    case dropdown_state::DROPDOWN_HIDDEN:
                        //should never happen
                    break;
                    case dropdown_state::DROPDOWN_CLICKED_ON:
                        //nothing happens
                    break;
                    case dropdown_state::DROPDOWN_CLICKED_OFF:
                        this->state = dropdown_state::DROPDOWN_CLICKED_ON;
                    break;

                }
            }
            else{
                switch(this->state){
                    case dropdown_state::DROPDOWN_IDLE:
                        //nothing happens
                    break;
                    case dropdown_state::DROPDOWN_HOVER:
                        this->state = dropdown_state::DROPDOWN_IDLE;
                    break;
                    case dropdown_state::DROPDOWN_HIDDEN:
                        //should never happen
                    break;
                    case dropdown_state::DROPDOWN_CLICKED_ON:
                        //nothing happens
                        this->state = dropdown_state::DROPDOWN_CLICKED_OFF;
                    break;
                    case dropdown_state::DROPDOWN_CLICKED_OFF:
                        
                    break;

                }
            }

        break;

        

        case sf::Event::MouseButtonPressed:
            if(e.mouseButton.button == sf::Mouse::Left){
                switch(this->state){
                    case dropdown_state::DROPDOWN_IDLE:
                        //nothing happens
                    break;
                    case dropdown_state::DROPDOWN_HOVER:
                        this->state = dropdown_state::DROPDOWN_CLICKED_ON;                
                    break;
                    case dropdown_state::DROPDOWN_HIDDEN:
                        //should never happen
                    break;
                    case dropdown_state::DROPDOWN_CLICKED_ON:
                        //shouldn't be possible
                    break;
                    case dropdown_state::DROPDOWN_CLICKED_OFF:
                        //shouldn't be possible
                    break;

                }
            }

        break;

        case sf::Event::MouseButtonReleased:
            if(e.mouseButton.button == sf::Mouse::Left){
                switch(this->state){
                    case dropdown_state::DROPDOWN_IDLE:
                    //nothing happens
                    break;
                    case dropdown_state::DROPDOWN_HOVER:
                    //shouldn't be possible
                    break;
                    case dropdown_state::DROPDOWN_HIDDEN:
                    //should never happen
                    break;
                    case dropdown_state::DROPDOWN_CLICKED_ON:
                        this->state = dropdown_state::DROPDOWN_HOVER;
                    break;
                    case dropdown_state::DROPDOWN_CLICKED_OFF:
                        this->state = dropdown_state::DROPDOWN_IDLE;
                    break;

                }
            }

        break;
        default:
        break;

    }

    
    for(auto i = this->items.begin(); i != this->items.end(); ++i){
                
        i->second.notify(e);
    }


}



