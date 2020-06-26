#include "Visualization.hpp"

#pragma region Constructors

Visualization::Visualization(int width, int height)
{

    //create main window object
    this->window = new sf::RenderWindow(sf::VideoMode(width, height), "Simulation");
    this->height = height;
    this->width = width;
    this->state = nullptr;
}

Visualization::~Visualization()
{
}

#pragma endregion

#pragma region Main Functionality
void Visualization::render()
//render all data and controls to screen
{

    if (this->state != nullptr)
    {
        this->state->render(this->window);
    }
    this->window->display();
}

void Visualization::handleEvents()
//handle gui events
{

    while (this->window->pollEvent(this->event))
    {
        this->state->handleEvent(this->event);

        if (this->event.type == sf::Event::Closed)
        {
            this->window->close();
        }
    }
}

void Visualization::setState(ApplicationState *state)
{
    this->state = state;
}

sf::RenderWindow *Visualization::getWindowHandle()
{
    return this->window;
}

#pragma endregion

#pragma region Getters

bool Visualization::isOpen()
//return if window is open
{
    return this->window->isOpen();
}

#pragma endregion
