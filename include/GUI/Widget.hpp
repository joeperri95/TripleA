#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <SFML/Graphics.hpp>
#include <string>


class Widget{

public:

    Widget();
    ~Widget();

    virtual void update();
    virtual void render(sf::RenderTarget *target);
    virtual void notify(sf::Event e);

protected:
    int x, y;
    std::string name;

};

#endif