#include "sequencer.hpp"

Sequencer::Sequencer(int numButtons, double stepTime)
{
    this->stepTime = stepTime;
    this->numButtons = numButtons;
    this->init();
}

Sequencer::Sequencer()
{
}

Sequencer::~Sequencer()
{

    delete this->track;
    delete this->dev;
}

void Sequencer::init()
{

    this->currentButton = 0;
    this->track = new Track(this->numButtons * this->stepTime);
    this->track->setLoop(true);

    this->dev = new AlsaDevice("default", 44100, 2, 512, 2);

    this->dev->setAudioObject(this->track);
    this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "sequencer", sf::Style::Close);

    currentTime = std::chrono::system_clock::now();
    stepStart = currentTime;

    int rows = 4;

    for (int j = 0; j < rows; j++)
    {
        for (int i = 0; i < this->numButtons; i++)
        {
            this->buttons.insert(std::pair<int, seqButton *>(i, new seqButton(X_OFFSET + i * (BUTTON_WIDTH + SPACER), Y_OFFSET, BUTTON_WIDTH, BUTTON_HEIGHT)));
            this->buttonStates.insert(std::pair<int, bool>(i, false));
        }
    }
}

void Sequencer::render(sf::RenderTarget *target)
{

    this->window->clear(sf::Color::Black);

    for (int i = 0; i < 4; i++)
    {
        for (int i = 0; i < this->numButtons; i++)
        {
            this->buttons[i]->render(target);
        }
    }

    this->window->display();
}

void Sequencer::update()
{

    while (this->window->pollEvent(this->event))
    {
        if (this->event.type == sf::Event::Closed)
        {
            this->window->close();
        }

        for (auto i = this->buttons.begin(); i != this->buttons.end(); ++i)
        {
            i->second->notify(this->event);
        }
    }

    for (int i = 0; i < this->numButtons; i++)
    {

        bool state = i == this->currentButton ? true : false;
        this->buttons[i]->setStatus(state);
        this->buttons[i]->update();

        if (this->buttons[i]->getFlag())
        {
            //this->buttons[i]->setFlag(false);

            if (this->buttonStates[i])
            {
                this->buttonStates[i] = false;
                this->dev->pause();
                this->track->removeTone(i);
                this->dev->setAudioObject(this->track);
                this->dev->resume();
            }
            else if (!this->buttonStates[i])
            {
                this->buttonStates[i] = true;
                this->dev->pause();
                //this->track->addTone(i, new PCMTone("res/wavs/pp.wav",i * stepTime, (i+1) * stepTime ));
                this->track->addTone(i, new Sine(i * stepTime, (i + 1) * stepTime, 0.5, 220));
                this->dev->setAudioObject(this->track);
                this->dev->resume();
            }
        }
    }

    this->buttons[this->currentButton]->setStatus(true);

    this->currentTime = std::chrono::system_clock::now();
    this->stepPeriod = this->currentTime - this->stepStart;

    if (this->stepPeriod.count() > this->stepTime)
    {
        this->currentButton = this->currentButton == (this->numButtons - 1) ? 0 : this->currentButton + 1;
        this->stepStart = this->currentTime;
    }
}

void Sequencer::run()
{

    while (this->window->isOpen())
    {

        this->update();
        this->render(this->window);
    }
}

void Sequencer::addTrackEffect(int index, Effect *e)
{

    //no index for now
    this->track->addEffect(e);
}

void Sequencer::setTrackTone(int index, Tone *t)
{

    this->tones.insert(std::pair<int, Tone *>(index, t));
}

void Sequencer::setStepTime(double step)
{
    this->stepTime = step;
}