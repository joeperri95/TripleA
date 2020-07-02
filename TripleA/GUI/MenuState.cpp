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
    
    nlohmann::json rawJSON, widgetListJSON;
    layoutFile >> rawJSON;

    widgetListJSON = rawJSON["Widgets"];
    int numWidgets = widgetListJSON["count"];

    for (int i = 0; i < numWidgets; i++)
    {
        if (widgetListJSON["list"][i]["type"] == "Button")
        {
            Button *b = new Button();
            b->setPosition(sf::Vector2f(widgetListJSON["list"][i]["position"][0], widgetListJSON["list"][i]["position"][1]));
            b->setName(widgetListJSON["list"][i]["name"]);

            if (widgetListJSON["list"][i]["idlecolor"] != nullptr)
                b->idleColor = sf::Color(widgetListJSON["list"][i]["idlecolor"][0], widgetListJSON["list"][i]["idlecolor"][1], widgetListJSON["list"][i]["idlecolor"][2]);
            if (widgetListJSON["list"][i]["size"] != nullptr)
            {
                b->setSize(widgetListJSON["list"][i]["size"][0], widgetListJSON["list"][i]["size"][1]);
            }

            this->widgets.push_back(std::shared_ptr<IWidget>((IWidget *)(b)));
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
    Button *b = new Button();
    this->widgets.push_back(std::shared_ptr<IWidget>((IWidget *)b));
    b->setPosition(sf::Vector2f(200, 200));
    b->setName("name");
    
    Listener l1([](void * args){std::cout << "Pressed" << std::endl;}, nullptr);
    b->addListener(l1, button_event::PRESSED);
    Listener l2([](void * args){std::cout << "Released" << std::endl;}, nullptr);
    b->addListener(l2, button_event::RELEASED);
    Listener l3([](void * args)
    {
        ((Button *) args)->idleColor = sf::Color::Green;
    }, b);
    b->addListener(l3, button_event::ENTERED);
    Listener l4([](void * args)
    {
        ((Button *) args)->idleColor = sf::Color::Yellow;
    }, b);
    b->addListener(l4, button_event::LEFT);
}