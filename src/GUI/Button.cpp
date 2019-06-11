#include "../../include/GUI/Button.hpp"

Button::~Button(){

};


Button::Button(int x, int y, int width, int height, std::string text, sf::Font *font){
    
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(width, height));
    rect.setPosition(sf::Vector2f(x,y));
    rect.setFillColor(this->idleColor);
    this->rects.push_back(rect);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::Red);
    this->text.setCharacterSize(12);
    this->text.setPosition(0,0);
    this->text.setPosition(
        x + (width / 2.f) - width / 2.f,
        y + (height / 2.f) - height / 2.f     
    );

    this->state = button_state::IDLE;
    this->active = false;

    this->idleColor = sf::Color(0xFFFFFF70);
    this->hoverColor = sf::Color(0x77777770);
    this->clickedColor = sf::Color(0x00000070);

}

Button::Button(int x, int y, int width, int height, std::string text){
    
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(width, height));
    rect.setPosition(sf::Vector2f(x,y));
    rect.setFillColor(this->idleColor);
    this->rects.push_back(rect);

    this->font->loadFromFile("../../res/fonts/Ubuntu-R.ttf");
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::Red);
    this->text.setCharacterSize(12);
    this->text.setPosition(0,0);
    this->text.setPosition(
        x + (width / 2.f) - width / 2.f,
        y + (height / 2.f) - height / 2.f     
    );

    this->state = button_state::IDLE;
    this->active = false;

    this->idleColor = sf::Color(0xFFFFFF70);
    this->hoverColor = sf::Color(0x77777770);
    this->clickedColor = sf::Color(0x00000070);

}


void Button::render(sf::RenderTarget *target){
    for(auto i = this->rects.begin(); i!=this->rects.end(); ++i){
        target->draw(*i);
    }

    target->draw(this->text);
}

void Button::update(){
    
    if(this->active){

        for(auto i = this->listeners.begin(); i != this->listeners.end(); ++i){
            i->executeAsBackgroundThread();
        }

        this->active = false;
    }

    if(this->state == button_state::HOVER){
        for(auto i = this->rects.begin(); i!=this->rects.end(); ++i){
            i->setFillColor(this->hoverColor);
        }
        
    }
    else if(this->state == button_state::PRESSED_ON || this->state == button_state::PRESSED_OFF){
        for(auto i = this->rects.begin(); i!=this->rects.end(); ++i){
            i->setFillColor(this->clickedColor);
        }
    }
    else{
        for(auto i = this->rects.begin(); i!=this->rects.end(); ++i){
            i->setFillColor(this->idleColor);
        }
    }

}

void Button::addListener(Listener &l){
    this->listeners.push_back(l);
}

void Button::notify(sf::Event e){

    if(e.type == sf::Event::MouseMoved){
        
        bool inside = false;
        
        for(auto i = this->rects.begin(); i != this->rects.end(); ++i){
            if(i->getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y)))
                inside = true;
        }
            if(inside){
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

void Button::addRect(sf::RectangleShape &r){
    this->rects.push_back(r);
}

void Button::addRect(int x, int y, int w, int h){
    sf::RectangleShape r;
    r.setPosition(sf::Vector2f(x, y));
    r.setSize(sf::Vector2f(w, h));
    this->rects.push_back(r);
}