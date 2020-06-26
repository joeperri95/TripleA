#ifndef __WIDGET_H__
#define __WIDGET_H__

#include <SFML/Graphics.hpp>

class IWidget
{
public:
    IWidget();
    virtual ~IWidget();

    sf::Vector2f getPosition();
    void setName(std::string name);
    virtual void setPosition(sf::Vector2f newPosition);
    virtual void render(sf::RenderTarget *renderer) = 0;
    virtual void handleEvent(sf::Event &e) = 0;
    virtual void update() = 0;

protected:
    sf::Vector2f position;
    std::string name;
};

#endif