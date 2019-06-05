#ifndef __OSCILLOSCOPE_H__
#define __OSCILLOSCOPE_H__


#include <SFML/Graphics.hpp>
#include <string.h>

class Oscilloscope{

public: 
    Oscilloscope(int x, int y, int height, int width, short *data, int N);
    Oscilloscope();
    ~Oscilloscope();

    void plot();
    void render(sf::RenderTarget *target);
    void update();
    
private:

    int x, y, height, width;
    int data_length;
    int data_ptr_cnt;
    short *data;
    short *data_ptr;
    int numSamples;
    sf::Color lineColor;
    sf::VertexArray line;
    sf::RectangleShape background;

};

#endif