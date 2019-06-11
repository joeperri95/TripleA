#ifndef __DROPDOWN_MENU_H__
#define __DROPDOWN_MENU_H__

#include "Widget.hpp"
#include "DropDownItem.hpp"
#include <string>


class DropDownMenu : public Widget{

public:

    
    ~DropDownMenu();
    DropDownMenu(int height, std::string name);
    DropDownMenu(int height, int width, std::string name);

    std::string getName();
    void addItem(DropDownItem &item);
    void addItem(std::string text);
    void setPosition(int x, int y);
    void setState(dropdown_state newState);
    dropdown_state getState();

    sf::RectangleShape getRect();
    void notify(sf::Event e);
    void render(sf::RenderTarget *target);
    void update();

private:
    
    int boxHeight;
    int boxWidth;
    int buttonHeight;
    int buttonWidth;

    dropdown_state state;
    int numberOfItems;
    sf::RectangleShape rect;
    std::string name;
    sf::Text text;
    sf::Font font;
    std::map<std::string, DropDownItem> items;

};

#endif