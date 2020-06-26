#include "IWidget.h"

IWidget::IWidget()
{
}

IWidget::~IWidget()
{
}

void IWidget::setPosition(sf::Vector2f newPosition)
{
    this->position = newPosition;
}

void IWidget::setName(std::string name)
{
    this->name = name;
}

sf::Vector2f IWidget::getPosition()
{
    return this->position;
}