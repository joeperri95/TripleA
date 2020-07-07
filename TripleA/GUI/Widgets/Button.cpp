#include "Button.h"

Button::Button()
{
    this->state = button_state::BUTTON_IDLE;
    this->name = "btn";

    //temporary delete this later
    this->size = sf::Vector2f(50, 25);
    this->rect.setFillColor(sf::Color(0x3F, 0x3F, 0x3F));
    //end

    this->rect.setSize(this->size);
}

Button::~Button()
{
}

void Button::handleEvent(sf::Event &e)
{
    if (e.type == sf::Event::MouseMoved)
    {

        bool inside = false;

        if (this->rect.getGlobalBounds().contains(sf::Vector2f(e.mouseMove.x, e.mouseMove.y)))
            inside = true;

        if (inside)
        {
            switch (this->state)
            {
            case BUTTON_IDLE:
                this->notify(button_event::BUTTON_ENTERED);
                this->state = button_state::BUTTON_HOVER;
                break;
            case BUTTON_HOVER:
                this->state = button_state::BUTTON_HOVER;
                break;
            case BUTTON_PRESSED_ON:
                this->state = button_state::BUTTON_PRESSED_ON;
                break;
            case BUTTON_PRESSED_OFF:
                this->state = button_state::BUTTON_PRESSED_ON;
                break;
            }
        }
        else
        {

            switch (this->state)
            {
            case BUTTON_IDLE:
                this->state = button_state::BUTTON_IDLE;
                break;
            case BUTTON_HOVER:
                this->state = button_state::BUTTON_IDLE;
                this->notify(button_event::BUTTON_LEFT);
                break;
            case BUTTON_PRESSED_ON:
                this->state = button_state::BUTTON_PRESSED_OFF;
                break;
            case BUTTON_PRESSED_OFF:
                this->state = button_state::BUTTON_PRESSED_OFF;
                break;
            }
        }
    }
    else if (e.type == sf::Event::MouseButtonPressed)
    {
        if (e.mouseButton.button == sf::Mouse::Left)
        {
            switch (this->state)
            {
            case BUTTON_IDLE:
                this->state = button_state::BUTTON_IDLE;
                break;
            case BUTTON_HOVER:
                this->state = button_state::BUTTON_PRESSED_ON;
                this->notify(button_event::BUTTON_PRESSED);
                break;
            case BUTTON_PRESSED_ON:
                this->state = button_state::BUTTON_PRESSED_ON;
                break;
            case BUTTON_PRESSED_OFF:
                this->state = button_state::BUTTON_PRESSED_OFF;
                break;
            }
        }
    }
    else if (e.type == sf::Event::MouseButtonReleased)
    {
        if (e.mouseButton.button == sf::Mouse::Left)
        {
            switch (this->state)
            {
            case BUTTON_IDLE:
                this->state = button_state::BUTTON_IDLE;
                break;
            case BUTTON_HOVER:
                this->state = button_state::BUTTON_HOVER;
                break;
            case BUTTON_PRESSED_ON:
                this->state = button_state::BUTTON_HOVER;
                this->notify(button_event::BUTTON_RELEASED);
                break;
            case BUTTON_PRESSED_OFF:
                this->state = button_state::BUTTON_IDLE;
                this->notify(button_event::BUTTON_RELEASED);
                break;
            }
        }
    }
}

void Button::render(sf::RenderTarget *renderer)
{
    renderer->draw(this->rect);
}

void Button::update()
//this is called periodically
{

}

void Button::addListener(Listener &listener, button_event event)
{
    this->listeners[event].push_back(listener);
}

void Button::notify(button_event event)
{
    for(auto it = this->listeners[event].begin(); it != this->listeners[event].end(); it++)
    {
        it->execute();
    }
}

void Button::setBackgroundColour(sf::Color colour)
{
    this->rect.setFillColor(colour);
}

void Button::setSize(int width, int height)
{
    this->size = sf::Vector2f(width, height);
    this->rect.setSize(this->size);
}
void Button::setSize(sf::Vector2f newSize)
{
    this->size = newSize;
    this->rect.setSize(this->size);
}

void Button::setPosition(sf::Vector2f newPosition)
//overide set position to move actual rect
{
    this->position = newPosition;
    this->rect.setPosition(newPosition);
}
