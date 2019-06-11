#include "../../include/GUI/DropDownMenuBar.hpp"


DropDownMenuBar::DropDownMenuBar(){

}

DropDownMenuBar::~DropDownMenuBar(){

}

DropDownMenuBar::DropDownMenuBar(int height, int width){
    this->barHeight = height;
    this->barWidth = width;
    this->nextMenuPos = 0;
    this->rect.setSize(sf::Vector2f(height, width));
    this->rect.setPosition(sf::Vector2f(0,0));
    this->rect.setFillColor(sf::Color(0xFF0000FF));
    this->numberOfItems = 0;
    this->state = dropdown_state::DROPDOWN_IDLE;
}

void DropDownMenuBar::addDropDownItem(DropDownItem &item){

    this->numberOfItems++;
    item.setPosition(this->nextMenuPos, 0);
    item.setState(dropdown_state::DROPDOWN_IDLE);
    this->nextMenuPos += item.getWidth();
    this->items.insert(std::pair<std::string, DropDownItem>(item.getName(), item));

}

void DropDownMenuBar::addDropDownMenu(DropDownMenu &menu){

    this->numberOfItems++;
    menu.setPosition(this->nextMenuPos, 0);
    this->nextMenuPos += menu.getRect().getSize().x;
    this->subMenus.insert(std::pair<std::string, DropDownMenu>(menu.getName(), menu));

}

void DropDownMenuBar::update(){
    for(auto i = this->subMenus.begin(); i != this->subMenus.end(); ++i){
        i->second.update();
    }
    for(auto i = this->items.begin(); i != this->items.end(); ++i){
        i->second.update();
    }
}

void DropDownMenuBar::render(sf::RenderTarget *target){

    target->draw(this->rect);

    for(auto i = this->subMenus.begin(); i != this->subMenus.end(); ++i){
        i->second.render(target);
    }
    for(auto i = this->items.begin(); i != this->items.end(); ++i){
        i->second.render(target);
    }
}

void DropDownMenuBar::notify(sf::Event e){
    //should this handle all logic?
    //should this handle no logic?
    for(auto i = this->subMenus.begin(); i != this->subMenus.end(); ++i){
        i->second.notify(e);
    }
    for(auto i = this->items.begin(); i != this->items.end(); ++i){
        i->second.notify(e);
    }
}