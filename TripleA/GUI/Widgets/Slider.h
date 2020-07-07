#ifndef __SLIDER_H__
#define __SLIDER_H__

#include "IWidget.h"
#include "Listener.h"

enum slider_state{
    SLIDER_IDLE,        
    SLIDER_HOVERING,   //hovering over slider box
    SLIDER_PRESS_ON,   //slider box has been clicked and mouse is still over box
    SLIDER_PRESS_OFF  //mouse is held down but no longer over box
    
};

enum slider_event{
    SLIDER_ENTER,
    SLIDER_LEFT,
    SLIDER_PRESSED,
    SLIDER_RELEASED,
    SLIDER_MOVED
};

template <typename T>
class Slider : IWidget{
/*
    A slider widget that uses numeric types
*/
public:
    Slider();
    ~Slider();

    void render(sf::RenderTarget *renderer);
    void handleEvent(sf::Event &e);
    void update();

    void addListener(Listener &l, slider_event event);
    
    T getValue();
    T getMaxValue();
    T getMinValue();

    void setValue(T value);
    void notify(slider_event event);

private:

    //functionality related
    T value;
    T minValue;
    T maxValue;
    slider_state state;
    std::map<slider_event, std::vector<Listener>> listeners;

    //visualization
    sf::RectangleShape bar;
    sf::RectangleShape box;
    sf::Color barColour;
    sf::Color boxColour;


    //event command handlers
    void _handleMousePress(sf::Event &e);
    void _handleMouseRelease(sf::Event &e);
    void _handleMouseMove(sf::Event &e);


};


#endif