#include "Audio/Audio.hpp"
#include "GUI/GUI.hpp"
#include <chrono>

class seqButton;

class Sequencer : public App{

public:
    Sequencer(int numButtons, double stepTime);
    Sequencer();
    ~Sequencer();


    void update();
    void render(sf::RenderTarget *target);
    void run();
    void pause();


private:

    void init();

    int currentButton;
    int numButtons;
    double stepTime;
    std::map<int, seqButton *> buttons;
    std::map<int, bool> buttonStates;

    std::chrono::system_clock::time_point currentTime;
    std::chrono::system_clock::time_point stepStart;
    std::chrono::duration<double> stepPeriod; 

    Track *track;
    AlsaDevice *dev;

};


class seqButton : public Widget{
    
    public:

        enum btnState{
            IDLE,
            HOVER,
            LATCHED_ON,
            LATCHED_OFF
        };


        seqButton(int x, int y, int width, int height){
            this->x = x;
            this->y = y;
            this->height = height;
            this->width = width;  
            this->state = btnState::IDLE;
            this->prevState = btnState::IDLE;
            this->flag = false;
            this->rect.setPosition(sf::Vector2f(x,y));
            this->rect.setSize(sf::Vector2f(width, height));

            this->addTexture("idle", "res/imgs/itried.png");
            this->addTexture("hover", "res/imgs/itried.png");
            this->addTexture("latched", "res/imgs/itried2.png");
            this->addTexture("active", "res/imgs/active.png");

            this->rect.setTextureRect(sf::IntRect(0, 0, this->width, this->height));
            this->rect.setTexture(this->textures["idle"]);
            this->rect.setOutlineColor(sf::Color::Black);
            

        }

        ~seqButton(){
            for(auto i = this->textures.begin(); i !=this->textures.end(); ++i){
                free(i->second);   
            }
            
        }

        void setStatus(bool active){
            this->active = active;
            
        }

        bool getFlag(){
            if(this->flag){
                this->flag = false;
                return true;
            }
            else{
                return false;
            }
            
        }

        void setFlag(bool f){
            this->flag = f;
        }

        void update(){

            this->updateTexture();

        }

        void updateTexture(){
            
            if(this->active){
                this->rect.setTexture(this->textures["active"]);
                //this->rect.setFillColor(sf::Color::Green);
            }
            else{

                switch(this->state){
                    case IDLE:
                        this->rect.setTexture(this->textures["idle"]);
                        //this->rect.setFillColor(sf::Color::Blue);
                        this->rect.setOutlineThickness(0);
                    break;
                    case HOVER:
                        this->rect.setTexture(this->textures["hover"]);
                        //this->rect.setFillColor(sf::Color::Yellow);
                        this->rect.setOutlineThickness(0);
                    break;
                    case LATCHED_ON:
                        this->rect.setTexture(this->textures["latched"]);
                        //this->rect.setFillColor(sf::Color::Red);
                        this->rect.setOutlineThickness(1);
                    break;
                    case LATCHED_OFF:
                        this->rect.setTexture(this->textures["latched"]);
                        //this->rect.setFillColor(sf::Color::Red);
                        this->rect.setOutlineThickness(1);
                    break;
                }
            }

        }

        void render(sf::RenderTarget *target){
            target->draw(this->rect);
        }

        void notify(sf::Event e){
            switch(e.type){
                case sf::Event::MouseMoved:
                    if(this->rect.getGlobalBounds().contains(e.mouseMove.x, e.mouseMove.y)){
                        if(this->state == btnState::IDLE){
                            this->prevState = this->state;
                            this->state = btnState::HOVER;
                        }
                        else if(this->state == btnState::LATCHED_OFF){
                            this->prevState = this->state;
                            this->state = btnState::LATCHED_ON;
                        }
                    }
                    else{
                        if(this->state == btnState::HOVER){
                            this->prevState = this->state;
                            this->state = btnState::IDLE;
                        }
                        else if(this->state == btnState::LATCHED_ON){
                            this->prevState = this->state;
                            this->state = btnState::LATCHED_OFF;
                        }
                    }

                break;


                case sf::Event::MouseButtonPressed:
                    if(e.mouseButton.button == sf::Mouse::Left){
                        if(this->state == btnState::HOVER){
                            this->prevState = this->state;
                            this->flag = true;
                            this->state = btnState::LATCHED_ON;
                        }
                        else if(this->state == btnState::LATCHED_ON){
                            this->prevState = this->state;
                            this->flag = true;
                            this->state = btnState::HOVER;
                        }
                    }
                break;


                case sf::Event::MouseButtonReleased:
                    //do something??
                break;
                default:
                break;

            }
        }


    private:

        int height;
        int width;
        bool active;
        std::atomic<bool> flag;
        sf::RectangleShape rect;
        btnState state;
        btnState prevState;
};