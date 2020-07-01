#include "Layout.h"

Layout::Layout()
{

}

Layout::Layout(std::string layoutFile)
{
    /*
        Create layout from JSON file
    */

    std::ifstream layoutFile(layoutFile);
    
    json rawJSON, widgetListJSON;
    layoutFile >> rawJSON;

    widgetListJSON = rawJSON["Widgets"];
    int numWidgets = widgetListJSON["count"];
    

    for (int i = 0; i < numWidgets; i++)
    {
        if (widgetListJSON["list"][i]["type"] == "Button")
        {
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


}

Layout::~Layout()
{

}

void Layout::addWidget(IWidget *widget)
{

}

void Layout::handleEvent(sf::Event &e)
{
    
    for (auto it = this->widgets.begin(); it != this->widgets.end(); it++)
        (*it)->handleEvent(e);

}

void Layout::render(sf::RenderTarget *renderer)
{
    renderer->clear(this->backgroundColor);
    for (auto it = this->widgets.begin(); it != this->widgets.end(); it++)
    {
        (*it)->render(renderer);
    }
}

void Layout::update()
{
    for (auto it = this->widgets.begin(); it != this->widgets.end(); it++)
    {
        (*it)->update();
    }
}