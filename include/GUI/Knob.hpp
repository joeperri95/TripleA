#ifndef __KNOB_H__
#define __KNOB_H__

#include "Widget.hpp"

typedef enum {
    KNOB_IDLE,
    KNOB_HOVER,
    KNOB_CLICKED_ON,
    KNOB_CLICKED_OFF

}knob_state;


class Knob : public Widget{

public:

    Knob(int x, int y, int radius);
    ~Knob();

    void render(sf::RenderTarget *target);
    void update();
    void notify(sf::Event e);

private:

    int radius;
    int minValue, maxValue;
    int *value;
    sf::CircleShape knobCircle;
    sf::RectangleShape line;    
    knob_state state;

};

#endif