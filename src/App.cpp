#include "../include/App.hpp"

App::App(){
    
    this->title = "App";
    this->height = 600;
    this->width = 800;
    this->init();

    
}

App::App(std::string title){
    this->height = 600;
    this->width = 800;
    this->title = title;
    this->init();
}

App::App(std::string title, int height, int width){
    this->height = height;
    this->width = width;
    this->title = title;

    this->init();
}


App::~App(){
    delete this->window;
}

void App::init(){
    this->window = new sf::RenderWindow(sf::VideoMode(this->width,this->height), this->title);
    
}

void App::render(){

    this->window->clear(sf::Color(0x303030FF));

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

    for(auto i = this->knobs.begin(); i != this->knobs.end(); ++i){
        i->render(this->window);
    }

    this->dropdown.render(this->window);

    this->window->display();
}

void App::update(){

    while(this->window->pollEvent(this->event)){
        if(this->event.type == sf::Event::Closed){
            this->window->close();
        }

        for(auto i = this->buttons.begin(); i != this->buttons.end(); ++i){
            i->notify(this->event);
        }     

        for(auto i = this->sliders.begin(); i != this->sliders.end(); ++i){
            i->notify(this->event);
        }

        this->dropdown.notify(this->event);
    } 
    
    sf::Vector2f floatPos( (float) sf::Mouse::getPosition(*this->window).x ,sf::Mouse::getPosition(*this->window).y);

    for(auto i = this->buttons.begin(); i != this->buttons.end(); ++i){
        i->update();
    }
    
    for(auto i = this->sliders.begin(); i != this->sliders.end(); ++i){
        i->update();
    }

    for(auto i = this->knobs.begin(); i != this->knobs.end(); ++i){
        i->update();
    }

    this->dropdown.update();

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
    
};

void App::addDropDown(DropDownMenuBar &dropdown){
    this->dropdown = dropdown;
}

void App::addKnob(Knob &k){
    this->knobs.push_back(k);
}

void App::addButton(Button &b){
    this->buttons.push_back(b);
}

void App::addSlider(Slider &s){
    this->sliders.push_back(s);
}