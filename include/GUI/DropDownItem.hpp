#ifndef __DROPDOWN_ITEM_H__
#define __DROPDOWN_ITEM_H__

#include <string>
#include "Widget.hpp"
#include "Listener.hpp"

typedef enum{
    DROPDOWN_HIDDEN,
    DROPDOWN_IDLE,
    DROPDOWN_HOVER,
    DROPDOWN_CLICKED_ON,
    DROPDOWN_CLICKED_OFF

}dropdown_state;

class DropDownItem : public Widget{

public:
    DropDownItem(int height, int width, std::string name);
    DropDownItem(std::string name, int height);
    ~DropDownItem();

    std::string getName();
    void addListener(Listener &l);
    void setSize(int height, int width);
    void setPosition(int x, int y);
    void setState(dropdown_state newState);

    void notify(sf::Event e);
    void render(sf::RenderTarget *target);
    void update();

    dropdown_state getState();
    int getWidth();
    int getHeight();

private:

    dropdown_state state;
    int height;
    int width;
    bool active;

    //only update on state change
    bool stateChangeFlag;
    
    sf::RectangleShape rect;
    std::string name;
    sf::Text text;
    sf::Font font;
    std::vector<Listener> listeners;

};

#endif