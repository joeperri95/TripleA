#ifndef __APP_H__
#define __APP_H__

#include <SFML/Graphics.hpp>
#include "Device.hpp"
#include "Button.hpp"
#include "Slider.hpp"
#include "Oscilloscope.hpp"

//remove
#include "Track.hpp"
#include "Tones/PCMTone.hpp"
#include "Tones/Sine.hpp"

class App{

public:
    App();
    ~App();

    void init();
    void run();
    void render(); 
    void update();

    void addButton(Button &b);
    void addSlider(Slider &s);
    void addText(sf::Text, int x, int y);
    
    void addImage(sf::Texture tex, int x, int y);
    void addImage(std::string str, int x, int y);
    void addText(sf::Text);

private:
    sf::RenderWindow *window;
    sf::Event event;
    Device *device;
    
    int volume;

    std::vector<Button> buttons;
    std::vector<Slider> sliders;
    std::vector<sf::Sprite> images;
    std::vector<sf::Texture> textures;
};

#endif