#include "Button.h"

Button::Button()
{
    this->state = button_state::IDLE;
    this->active = false;
    this->name = "btn";

    //temporary delete this later
    this->size = sf::Vector2f(50, 25);
#define IDLE_COLOR sf::Color::Yellow
#define HOVER_COLOR sf::Color::Blue
#define CLICKED_COLOR sf::Color::Red
    this->rect.setFillColor(IDLE_COLOR);
    //end

    this->idleColor = IDLE_COLOR;
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
            case IDLE:
                this->state = button_state::HOVER;
                break;
            case HOVER:
                this->state = button_state::HOVER;
                break;
            case PRESSED_ON:
                this->state = button_state::PRESSED_ON;
                break;
            case PRESSED_OFF:
                this->state = button_state::PRESSED_ON;
                break;
            }
        }
        else
        {

            switch (this->state)
            {
            case IDLE:
                this->state = button_state::IDLE;
                break;
            case HOVER:
                this->state = button_state::IDLE;
                break;
            case PRESSED_ON:
                this->state = button_state::PRESSED_OFF;
                break;
            case PRESSED_OFF:
                this->state = button_state::PRESSED_OFF;
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
            case IDLE:
                this->state = button_state::IDLE;
                break;
            case HOVER:
                this->state = button_state::PRESSED_ON;
                break;
            case PRESSED_ON:
                this->state = button_state::PRESSED_ON;
                break;
            case PRESSED_OFF:
                this->state = button_state::PRESSED_OFF;
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
            case IDLE:
                this->state = button_state::IDLE;
                break;
            case HOVER:
                this->state = button_state::HOVER;
                break;
            case PRESSED_ON:
                this->active = true;
                this->state = button_state::HOVER;
                break;
            case PRESSED_OFF:
                this->active = true;
                this->state = button_state::IDLE;
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
    if (this->active)
    //execute function if clicked and released
    {
        std::cout << "clicked " << this->name << std::endl;
        this->active = false;
    }

    if (this->state == button_state::HOVER)
    {
        rect.setFillColor(HOVER_COLOR);
    }
    else if (this->state == button_state::PRESSED_ON || this->state == button_state::PRESSED_OFF)
    {
        rect.setFillColor(CLICKED_COLOR);
    }
    else
    {
        rect.setFillColor(this->idleColor);
    }
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