#include "MenuState.h"

#pragma region Constructors
MenuState::MenuState()
{
    this->backgroundColor = sf::Color(0xF, 0xF, 0xF);
    this->_initializeWidgets();
}

MenuState::MenuState(std::string filename)
{

    //testing code

    std::ifstream layoutFile(filename);
    
    json rawJSON, widgetListJSON;
    layoutFile >> rawJSON;

    widgetListJSON = rawJSON["Widgets"];
    int numWidgets = widgetListJSON["count"];
    std::cout << numWidgets << std::endl;

    for (int i = 0; i < numWidgets; i++)
    {
        if (widgetListJSON["list"][i]["type"] == "Button")
        {
            std::cout << "bammmmm!" << std::endl;
            this->widgets.push_back(std::shared_ptr<IWidget>(new Button));
            auto b = (std::static_pointer_cast<Button>(this->widgets.back()));
            b->setPosition(sf::Vector2f(widgetListJSON["list"][i]["position"][0], widgetListJSON["list"][i]["position"][1]));
            b->setName(widgetListJSON["list"][i]["name"]);

            if (widgetListJSON["list"][i]["idlecolor"] != nullptr)
                b->idleColor = sf::Color(widgetListJSON["list"][i]["idlecolor"][0], widgetListJSON["list"][i]["idlecolor"][1], widgetListJSON["list"][i]["idlecolor"][2]);
            if (widgetListJSON["list"][i]["size"] != nullptr)
            {
                b->setSize(widgetListJSON["list"][i]["size"][0], widgetListJSON["list"][i]["size"][1]);
            }
        }
    }

    this->backgroundColor = sf::Color(0xF, 0xF, 0xF);
    this->_initializeWidgets();
}

MenuState::~MenuState()
{
}

#pragma endregion

#pragma region Inherited Methods
void MenuState::render(sf::RenderTarget *renderer)
//draw everything associated with state
{
    renderer->clear(this->backgroundColor);
    for (auto it = this->widgets.begin(); it != this->widgets.end(); it++)
    {
        (*it)->render(renderer);
    }
}

void MenuState::addWidget(std::shared_ptr<IWidget> widget)
{
    this->widgets.push_back(widget);
}

void MenuState::update()
{
    //std::cout << "updating" << std::endl;
    for (auto it = this->widgets.begin(); it != this->widgets.end(); it++)
    {
        (*it)->update();
    }
}

void MenuState::handleEvent(sf::Event &e)
//accept input from keyboard and mouse
{
    switch (e.type)
    {
    case sf::Event::KeyPressed:
        switch (e.key.code)
        {
        case sf::Keyboard::Escape:
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }

    for (auto it = this->widgets.begin(); it != this->widgets.end(); it++)
        (*it)->handleEvent(e);
}

#pragma endregion

void MenuState::_initializeWidgets()
//add widgets
{
}