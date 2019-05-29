#include "../../include/GUI/Oscilloscope.hpp"

#include <iostream>


Oscilloscope::Oscilloscope(){

}

Oscilloscope::~Oscilloscope(){
    free(this->data);
    free(this->data_ptr);   
}

Oscilloscope::Oscilloscope(int x, int y, int width, int height, short *data, int N){
    
    this->x = x;
    this->y = y;
    this->height = height;
    this->width = width;
    
    this->lineColor = sf::Color::Red;
    this->background.setPosition(x,y);
    this->background.setSize(sf::Vector2f(width, height));
    this->background.setFillColor(sf::Color::White);
    this->numSamples = width;
    
    this->data = (short *) malloc(N * sizeof(short));
    memcpy(this->data, data, N);    

    this->data_ptr = (short *) malloc( width * sizeof(short));
    this->data_ptr = this->data;
    
    this->data_length = N;
    this->data_ptr_cnt = 0;
}


void Oscilloscope::plot(){
    
    this->line.clear();

    for(int  i = 0; i < this->numSamples; i++){
        
        sf::Vector2f coords(this->x + i, this->y + this->height / 2.f + (((float) this->height / INT16_MAX) * *(this->data_ptr + i)));
        
        this->line.append(sf::Vertex(coords, this->lineColor));   
    }
    
}

void Oscilloscope::update(){
    
    if(this->data_ptr_cnt < this->data_length){
        this->data_ptr++;
        this->data_ptr_cnt++;
        
        if((this->data_ptr_cnt + this->numSamples) < (this->data_length))
            this->plot();

    }
    
}


void Oscilloscope::render(sf::RenderTarget *target){
    target->draw(this->background);
    target->draw(this->line);
}