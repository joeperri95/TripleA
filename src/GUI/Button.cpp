#include "../../include/GUI/Button.hpp"

Button::~Button(){

};


Button::Button(int x, int y, int width, int height, std::string text, sf::Font *font){
    
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
    this->active = false;

    this->idleColor = sf::Color(0xFFFFFF70);
    this->hoverColor = sf::Color(0x77777770);
    this->clickedColor = sf::Color(0x00000070);

    this->rect.setFillColor(this->idleColor);

}

void Button::render(sf::RenderTarget *target){
    target->draw(this->rect);
    target->draw(this->text);
}

void Button::update(){
    
    if(this->active){

        for(auto i = this->listeners.begin(); i != this->listeners.end(); ++i){
            i->Execute();
        }

        this->active = false;
    }

    if(this->state == button_state::HOVER){
        this->rect.setFillColor(this->hoverColor);
    }
    else if(this->state == button_state::PRESSED_ON || this->state == button_state::PRESSED_OFF){
        this->rect.setFillColor(this->clickedColor);
    }
    else{
        this->rect.setFillColor(this->idleColor);
    }

}

void Button::addListener(Listener &l){
    this->listeners.push_back(l);
}

void Button::notify(sf::Event e){

    if(e.type == sf::Event::MouseMoved){
        if(this->rect.getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y))){
            switch(this->state){
                case IDLE:
                    this->state = button_state::HOVER;
                    break;
                case HOVER:
                    this->state = button_state::HOVER;
                    break;
                case PRESSED_ON:
                    this->state = button_state::PRESSED_ON;
                    break;
                case PRESSED_OFF:
                    this->state = button_state::PRESSED_ON;
                    break;
            }

        }
        else{

            switch(this->state){
                case IDLE:
                    this->state = button_state::IDLE;
                    break;
                case HOVER:
                    this->state = button_state::IDLE;
                    break;
                case PRESSED_ON:
                    this->state = button_state::PRESSED_OFF;
                    break;
                case PRESSED_OFF:
                    this->state = button_state::PRESSED_OFF;
                    break;
            }

        }

    }
    else if(e.type == sf::Event::MouseButtonPressed){
        if(e.mouseButton.button == sf::Mouse::Left){
            switch(this->state){
                case IDLE:
                    this->state = button_state::IDLE;
                    break;
                case HOVER:
                    this->state = button_state::PRESSED_ON;
                    this->active = true;
                    break;
                case PRESSED_ON:
                    this->state = button_state::PRESSED_ON;
                    break;
                case PRESSED_OFF:
                    this->state = button_state::PRESSED_OFF;
                    break;

            }
        }
    }
    else if(e.type == sf::Event::MouseButtonReleased){
        if(e.mouseButton.button == sf::Mouse::Left){
            switch(this->state){
                case IDLE:
                    this->state = button_state::IDLE;
                    break;
                case HOVER:
                    this->state = button_state::HOVER;
                    break;
                case PRESSED_ON:
                    this->state = button_state::HOVER;
                    break;
                case PRESSED_OFF:
                    this->state = button_state::IDLE;
                    break;
            }
        }
    }

}

bool Button::isHovering(){
    if(this->state == button_state::HOVER){
        return true;
    }
    else{
        return false;
    }
}

bool Button::isPressed(){
    if(this->state == button_state::PRESSED_ON || this->state == button_state::PRESSED_OFF){
        return true;
    }
    else{
        return false;
    }
}