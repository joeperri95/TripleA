#include "../include/App.hpp"

App::App(){
    this->init();
}

App::~App(){
    delete this->window;
    delete this->device;
}

void App::init(){

    this->window = new sf::RenderWindow(sf::VideoMode(800,600), "App");
    this->device = new Device();
}

void App::render(){

    this->window->clear(sf::Color(0x101010FF));

    //draw widgets
    for(auto i = this->buttons.begin(); i != this->buttons.end(); ++i){
        i->render(this->window);
    }


    for(auto i = this->sliders.begin(); i != this->sliders.end(); ++i){
        i->render(this->window);
    }

    for(auto i = this->images.begin(); i != this->images.end(); ++i){
        this->window->draw(*i);
    }

    this->window->display();
}

void App::update(){

    while(this->window->pollEvent(this->event)){
        if(this->event.type == sf::Event::Closed){
            this->window->close();
        }            
    } 

    sf::Vector2f floatPos( (float) sf::Mouse::getPosition(*this->window).x ,sf::Mouse::getPosition(*this->window).y);

    for(auto i = this->buttons.begin(); i != this->buttons.end(); ++i){
        i->update(floatPos);
    }
    
    for(auto i = this->sliders.begin(); i != this->sliders.end(); ++i){
        i->update(floatPos);
    }


}

//main loop
void App::run(){

    while(this->window->isOpen()){
        
        this->update();
        this->render();

    }

}

void App::addImage(sf::Texture tex, int x, int y){
    sf::Sprite s(tex);
    s.setPosition(x, y);
    this->images.push_back(s);
    this->textures.push_back(tex);
}

void App::addImage(std::string s, int x, int y){
    sf::Texture tex;
    tex.loadFromFile(s);
    this->textures.push_back(tex);

    sf::Sprite spr(*(this->textures.end() - 1));
    spr.setPosition(x, y);
    this->images.push_back(spr);
    

}

void App::addButton(Button &b){
    this->buttons.push_back(b);
}

void App::addSlider(Slider &s){
    this->sliders.push_back(s);
}