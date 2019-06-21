#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <SFML/Graphics.hpp>
#include <string>


class Widget{

public:

    Widget();
    ~Widget();

    int getX();
    int getY();    

    virtual void update() = 0;
    virtual void render(sf::RenderTarget *target) = 0;
    virtual void notify(sf::Event e) = 0;

    void addTexture(std::string name, std::string filepath);

protected:
    int x, y;
    std::string name;
    std::map<std::string , sf::Texture *> textures;

};

#endif