#include "Cursor.hpp"

Cursor::Cursor()
{

    this->backgroundColour = sf::Color::Yellow;
    this->tipColour = sf::Color::Black;

    this->shape = sf::VertexArray(sf::PrimitiveType::Triangles);
    this->trail = sf::VertexArray(sf::PrimitiveType::LineStrip);

    //TODO make this an argument
    this->size = 20;

    //left triangle
    this->shape.append(sf::Vector2f(0, this->size));
    this->shape.append(sf::Vector2f(-this->size, -this->size));
    this->shape.append(sf::Vector2f(0, -this->size / 2));

    //right triangle
    this->shape.append(sf::Vector2f(0, this->size));
    this->shape.append(sf::Vector2f(this->size, -this->size));
    this->shape.append(sf::Vector2f(0, -this->size / 2));

    //colour triangles
    this->setFillColour(this->backgroundColour);
}

Cursor::~Cursor()
{
}

void Cursor::render(sf::RenderTarget *renderer)
//render cursor onto renderer
{
    renderer->draw(this->trail);
    renderer->draw(this->shape);
}

void Cursor::move(double x, double y)
//set position based on current position
{
    this->setPosition(this->centerPosition.x + x, this->centerPosition.y + y);
    this->trail.append(sf::Vertex(this->centerPosition, this->backgroundColour));
}

void Cursor::advance(double r)
//move by r in direction of angle
{
    this->setPosition(this->centerPosition.x + r * cos(this->angle + M_PI / 2), this->centerPosition.y + r * sin(this->angle + M_PI / 2));
    this->trail.append(sf::Vertex(this->centerPosition, this->backgroundColour));
}

void Cursor::rotateDegrees(double x)
//set rotation based on current angle
{
    this->setRotationRads(this->angle + x * M_PI / 180);
}

void Cursor::rotateRads(double x)
//set rotation based on current angle
{
    this->setRotationRads(this->angle + x);
}

#pragma region setters

void Cursor::setPosition(double x, double y)
//set position of cursor
{
    this->centerPosition = sf::Vector2f(x, y);
    this->trail.append(sf::Vertex(this->centerPosition, this->backgroundColour));
    
    double offsets[6] =
        {
            this->angle + (90) * M_PI / 180,
            this->angle + (225) * M_PI / 180,
            this->angle + (270) * M_PI / 180,
            this->angle + (90) * M_PI / 180,
            this->angle + (315) * M_PI / 180,
            this->angle + (270) * M_PI / 180

        };

    this->shape[0].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[0]), this->size * sin(offsets[0]) + centerPosition.y);
    this->shape[1].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[1]), this->size * sin(offsets[1]) + centerPosition.y);
    this->shape[2].position = sf::Vector2f(centerPosition.x + (this->size / 2) * cos(offsets[2]), (this->size / 2) * sin(offsets[2]) + centerPosition.y);

    this->shape[3].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[3]), this->size * sin(offsets[3]) + centerPosition.y);
    this->shape[4].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[4]), this->size * sin(offsets[4]) + centerPosition.y);
    this->shape[5].position = sf::Vector2f(centerPosition.x + (this->size / 2) * cos(offsets[5]), (this->size / 2) * sin(offsets[5]) + centerPosition.y);
}

void Cursor::setPosition(sf::Vector2f pos)
//set position of cursor
{


    
    double offsets[6] =
        {
            this->angle + (90) * M_PI / 180,
            this->angle + (225) * M_PI / 180,
            this->angle + (270) * M_PI / 180,
            this->angle + (90) * M_PI / 180,
            this->angle + (315) * M_PI / 180,
            this->angle + (270) * M_PI / 180

        };

    this->centerPosition = pos;
    this->trail.append(sf::Vertex(this->centerPosition, this->backgroundColour));
    this->shape[0].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[0]), this->size * sin(offsets[0]) + centerPosition.y);
    this->shape[1].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[1]), this->size * sin(offsets[1]) + centerPosition.y);
    this->shape[2].position = sf::Vector2f(centerPosition.x + (this->size / 2) * cos(offsets[2]), (this->size / 2) * sin(offsets[2]) + centerPosition.y);

    this->shape[3].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[3]), this->size * sin(offsets[3]) + centerPosition.y);
    this->shape[4].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[4]), this->size * sin(offsets[4]) + centerPosition.y);
    this->shape[5].position = sf::Vector2f(centerPosition.x + (this->size / 2) * cos(offsets[5]), (this->size / 2) * sin(offsets[5]) + centerPosition.y);
}

void Cursor::setFillColour(uint8_t r, uint8_t g, uint8_t b)
//set colour of cursor
{
    this->backgroundColour = sf::Color(r, g, b);
    this->shape[0].color = this->tipColour;
    this->shape[1].color = this->backgroundColour;
    this->shape[2].color = this->backgroundColour;
    this->shape[3].color = this->tipColour;
    this->shape[4].color = this->backgroundColour;
    this->shape[5].color = this->backgroundColour;
}

void Cursor::setFillColour(sf::Color color)
//set colour of cursor
{
    this->backgroundColour = color;
    this->shape[0].color = this->tipColour;
    this->shape[1].color = this->backgroundColour;
    this->shape[2].color = this->backgroundColour;
    this->shape[3].color = this->tipColour;
    this->shape[4].color = this->backgroundColour;
    this->shape[5].color = this->backgroundColour;
}

void Cursor::setTipColour(sf::Color color)
//set colour of the cursor tip
{
    this->tipColour = color;
    this->shape[0].color = this->tipColour;
    this->shape[1].color = this->backgroundColour;
    this->shape[2].color = this->backgroundColour;
    this->shape[3].color = this->tipColour;
    this->shape[4].color = this->backgroundColour;
    this->shape[5].color = this->backgroundColour;
}

void Cursor::setTipColour(uint8_t r, uint8_t g, uint8_t b)
//set colour of the cursor tip
{
    this->tipColour = sf::Color(r, g, b);
    this->shape[0].color = this->tipColour;
    this->shape[1].color = this->backgroundColour;
    this->shape[2].color = this->backgroundColour;
    this->shape[3].color = this->tipColour;
    this->shape[4].color = this->backgroundColour;
    this->shape[5].color = this->backgroundColour;
}

void Cursor::setRotationDegrees(double degrees)
{
    this->angle = degrees * M_PI / 180;

    double offsets[6] =
        {
            (degrees + 90) * M_PI / 180,
            (degrees + 225) * M_PI / 180,
            (degrees + 270) * M_PI / 180,
            (degrees + 90) * M_PI / 180,
            (degrees + 315) * M_PI / 180,
            (degrees + 270) * M_PI / 180

        };

    this->shape[0].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[0]), this->size * sin(offsets[0]) + centerPosition.y);
    this->shape[1].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[1]), this->size * sin(offsets[1]) + centerPosition.y);
    this->shape[2].position = sf::Vector2f(centerPosition.x + (this->size / 2) * cos(offsets[2]), (this->size / 2) * sin(offsets[2]) + centerPosition.y);

    this->shape[3].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[3]), this->size * sin(offsets[3]) + centerPosition.y);
    this->shape[4].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[4]), this->size * sin(offsets[4]) + centerPosition.y);
    this->shape[5].position = sf::Vector2f(centerPosition.x + (this->size / 2) * cos(offsets[5]), (this->size / 2) * sin(offsets[5]) + centerPosition.y);
}

void Cursor::setRotationRads(double rads)
{
    this->angle = rads;
    double offsets[6] =
        {
            rads + (90) * M_PI / 180,
            rads + (225) * M_PI / 180,
            rads + (270) * M_PI / 180,
            rads + (90) * M_PI / 180,
            rads + (315) * M_PI / 180,
            rads + (270) * M_PI / 180

        };

    this->shape[0].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[0]), this->size * sin(offsets[0]) + centerPosition.y);
    this->shape[1].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[1]), this->size * sin(offsets[1]) + centerPosition.y);
    this->shape[2].position = sf::Vector2f(centerPosition.x + (this->size / 2) * cos(offsets[2]), (this->size / 2) * sin(offsets[2]) + centerPosition.y);

    this->shape[3].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[3]), this->size * sin(offsets[3]) + centerPosition.y);
    this->shape[4].position = sf::Vector2f(centerPosition.x + this->size * cos(offsets[4]), this->size * sin(offsets[4]) + centerPosition.y);
    this->shape[5].position = sf::Vector2f(centerPosition.x + (this->size / 2) * cos(offsets[5]), (this->size / 2) * sin(offsets[5]) + centerPosition.y);
}

#pragma endregion

#pragma region getters

double Cursor::getDegrees()
{
    return this->angle * 180.f / M_PI;
}

double Cursor::getRadians()
{
    return this->angle;
}

sf::Vector2f Cursor::getPosition()
{
    return this->centerPosition;
}

#pragma endregion