#include "App.hpp"

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

    this->window->display();
}

void App::update(){

    while(this->window->pollEvent(this->event)){
        if(this->event.type == sf::Event::Closed){
            this->window->close();
        }            
    } 

    for(auto i = this->buttons.begin(); i != this->buttons.end(); ++i){
        
        sf::Vector2f floatPos( (float) sf::Mouse::getPosition(*this->window).x ,sf::Mouse::getPosition(*this->window).y);
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

void App::addButton(Button &b){
    this->buttons.push_back(b);
}