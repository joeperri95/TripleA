#ifndef __APPLICATION_STATE_H__
#define __APPLICATION_STATE_H__

#include <SFML/Graphics.hpp>

class ApplicationState
{

public:
    ApplicationState(){};
    virtual ~ApplicationState(){};

    virtual void handleEvent(sf::Event &event) = 0;
    virtual void render(sf::RenderTarget *renderer) = 0;
    virtual void update() = 0;

    virtual bool isClosing(){return this->closing;}

protected:
    bool closing = false;
};

#endif
