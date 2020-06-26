#ifndef __MENU_STATE_H__
#define __MENU_STATE_H__

#include <memory>
#include "ApplicationState.h"
#include "../Widgets/Widgets.h"
#include "nlohmann/json.hpp"
#include <fstream>

using json = nlohmann::json;

class MenuState : public ApplicationState
{
public:
    MenuState();
    MenuState(std::string filename);
    ~MenuState();

    void handleEvent(sf::Event &e);
    void render(sf::RenderTarget *renderer);
    void update();

    void addWidget(std::shared_ptr<IWidget> widget);

private:
    sf::Color backgroundColor;
    std::vector<std::shared_ptr<IWidget>> widgets;

    void _initializeWidgets();
};
#endif