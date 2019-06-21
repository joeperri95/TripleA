#include "GUI/Widget.hpp"

Widget::Widget(){}
Widget::~Widget(){}

int Widget::getX(){
    return this->x;
}

int Widget::getY(){
    return this->y;
}

void Widget::addTexture(std::string str, std::string filename){

    sf::Texture t;
    t.loadFromFile(filename);

    this->textures.insert(std::pair<std::string, sf::Texture *>(str, new sf::Texture(t)));
}