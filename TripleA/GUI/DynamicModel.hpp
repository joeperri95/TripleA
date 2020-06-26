#ifndef __DYNAMIC_MODEL_H__
#define __DYNAMIC_MODEL_H__

#include "Eigen/Dense"
#include <chrono>
#include <thread>

class DynamicModel
{
public:
    DynamicModel(bool threaded);
    ~DynamicModel();

    void setInput(int index, double value); 
    Eigen::VectorXd getState();
    void update();

private:
    double mass;
    double drag;

    Eigen::VectorXd state;
    Eigen::VectorXd input;
    Eigen::MatrixXd mapper; //map input to state
    Eigen::MatrixXd model;  //dynamic model

    void _updateJacobians();

    //sample period
    double period;

    //threading
    bool running;
    bool threaded; //if this should start thread
    std::shared_ptr<std::thread> loop;
    static void _updateLoop(void *args);
};

#endif