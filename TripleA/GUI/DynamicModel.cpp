#include "DynamicModel.hpp"

DynamicModel::DynamicModel(bool threaded)
{

    this->mass = 10.f;
    this->drag = 1.f;

    this->threaded = threaded;
    this->state.resize(6);
    this->model.resize(6, 6);
    this->mapper.resize(6, 2);
    this->input.resize(2);

    this->period = 20.f / 1000.f;

    this->state
        << 100,
        100, 0, 0, 0, 0;

    this->input << 0, 0;

    this->mapper << 0, 0,
        0, 0,
        0, 0,
        0, 0,
        1.f / this->mass, 0,
        0, 1.f / this->mass;

    this->model << 1, 0, this->period, 0, pow(this->period, 2) / 2, 0,
        0, 1, 0, this->period, 0, pow(this->period, 2) / 2,
        0, 0, 1, 0, this->period, 0,
        0, 0, 0, 1, 0, this->period,
        0, 0, -0.5 * this->drag , 0, 0, 0,
        0, 0, 0, -0.5 * this->drag, 0, 0;

    if (this->threaded)
    {
        this->running = true;
        this->loop = std::shared_ptr<std::thread>(new std::thread(this->_updateLoop, this));
    }
    else
    {
        this->running = false;
    }
}

DynamicModel::~DynamicModel()
{
}

void DynamicModel::update()
{
    this->_updateJacobians();
    this->state = this->model * this->state + this->mapper * this->input;
}

void DynamicModel::_updateJacobians()
//update jacobian of dynamic matrix
{
    this->model << 1, 0, this->period, 0, pow(this->period, 2) / 2, 0,
        0, 1, 0, this->period, 0, pow(this->period, 2) / 2,
        0, 0, 1, 0, this->period, 0,
        0, 0, 0, 1, 0, this->period,
        0, 0, -0.5 * this->drag, 0, 0, 0,
        0, 0, 0, -0.5 * this->drag, 0, 0;
}

void DynamicModel::_updateLoop(void *args)
//thread that is always running
{
    DynamicModel *me = (DynamicModel *)args;

    std::chrono::high_resolution_clock clk;
    std::chrono::time_point lastUpdate = clk.now();

    while (me->running)
    {
        if (std::chrono::duration_cast<std::chrono::milliseconds>(clk.now() - lastUpdate).count() > me->period)
        {
            lastUpdate = clk.now();
            me->update();
        }
    }
}

Eigen::VectorXd DynamicModel::getState()
{
    return this->state;
}

void DynamicModel::setInput(int index, double value)

{
    this->input(index) = value;
}