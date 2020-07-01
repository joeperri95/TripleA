#ifndef __LAYOUT_H__
#define __LAYOUT_H__

#include "Widgets.h"
#include <vector>
#include "nlohmann/json.hpp"
#include <fstream>


class Layout{

public:
    Layout();
    Layout(std::string layoutFile);
    ~Layout();

    void addWidget(IWidget *widget);

    void handleEvent(sf::Event &e);
    void render(sf::RenderTarget *renderer);
    void update();

private:
    
    std::vector<std::shared_ptr<IWidget>> widgets;
    

};


#endif