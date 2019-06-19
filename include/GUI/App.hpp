#ifndef __APP_H__
#define __APP_H__

#include <SFML/Graphics.hpp>
#include "Knob.hpp"
#include "Button.hpp"
#include "Slider.hpp"
#include "Oscilloscope.hpp"
#include "Widget.hpp"
#include "DropDownMenuBar.hpp"

class App{

public:
    App();
    App(std::string title);
    App(std::string title, int width, int height);
    ~App();

    void init();
    void run();
    void render(); 
    void update();

    void addButton(Button &b);
    void addSlider(Slider &s);
    void addText(sf::Text, int x, int y);
    void addKnob(Knob &k);
    void addDropDown(DropDownMenuBar &bar);

    void addImage(sf::Texture tex, int x, int y);
    void addImage(std::string str, int x, int y);
    void addText(sf::Text);

    int getHeight();
    int getWidth();

private:
    sf::RenderWindow *window;
    sf::Event event;
    
    std::string title;
    int height;
    int width;

    std::vector<Button> buttons;
    std::vector<Slider> sliders;
    std::vector<Knob> knobs;
    
    DropDownMenuBar dropdown;

    std::vector<sf::Sprite> images;
    std::vector<sf::Texture> textures;
};

#endif