#ifndef __DROPDOWN_MENUBAR_H__
#define __DROPDOWN_MENUBAR_H__

#include <string>
#include <vector>
#include "DropDownMenu.hpp"
#include "Widget.hpp"

class DropDownMenuBar : public Widget{

public:
    DropDownMenuBar();
    DropDownMenuBar(int height, int width);
    ~DropDownMenuBar();

    void addDropDownMenu(DropDownMenu &menu);
    void addDropDownItem(DropDownItem &item);

    void notify(sf::Event e);
    void render(sf::RenderTarget *target);
    void update();

private:

    dropdown_state state;
    
    //both submenus and items
    int numberOfItems;

    int barHeight;
    int barWidth;
    
    //next position of item
    int nextMenuPos;
    
    sf::RectangleShape rect;
    std::map<std::string, DropDownMenu> subMenus;
    std::map<std::string, DropDownItem> items;

};

#endif