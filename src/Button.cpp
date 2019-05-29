#include "../include/Button.hpp"

Button::~Button(){

};

Button::Button(float x, float y, float width, float height, std::string text, sf::Font *font){
    
    this->rect.setSize(sf::Vector2f(width, height));
    this->rect.setPosition(sf::Vector2f(x,y));
    
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::Red);
    this->text.setCharacterSize(12);
    this->text.setPosition(0,0);
    this->text.setPosition(
        this->rect.getPosition().x + (this->rect.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
        this->rect.getPosition().y + (this->rect.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f     
    );

    this->state = button_state::IDLE;

    this->idleColor = sf::Color(0xFFFFFF70);
    this->hoverColor = sf::Color(0x77777770);
    this->clickedColor = sf::Color(0x00000070);

    this->rect.setFillColor(this->idleColor);
    
}

void Button::render(sf::RenderTarget *target){
    target->draw(this->rect);
    target->draw(this->text);
}

void Button::update(sf::Vector2f mousePos){
    
    this->hover = false;
    this->pressed = false;

    if(this->rect.getGlobalBounds().contains(mousePos)){
        this->hover = true;
        
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(this->state == button_state::HOVER){
                this->state = button_state::PRESSED;
            }
        }
        else{
            if(this->state == button_state::IDLE){
                this->state = button_state::HOVER;
            }
            else if(this->state == button_state::PRESSED){
                this->state = button_state::HOVER;
            }
        }
    }
    
    else{
        
        this->state = button_state::IDLE;
    }

    if(this->state == button_state::HOVER){
        this->rect.setFillColor(this->hoverColor);
    }
    else if(this->state == button_state::PRESSED){
        this->rect.setFillColor(this->clickedColor);
        
    }
    else{
        this->rect.setFillColor(this->idleColor);
    }

}

bool Button::isHovering(){
    return this->hover;
}

bool Button::isPressed(){
    if(this->state == button_state::PRESSED){
        return true;
    }
    else{
        return false;
    }
}