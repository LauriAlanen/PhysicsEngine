#include <SimulatableObjects.hpp>

// #define DEBUG

Particle::~Particle()
{

}

// TODO: Possibly try Verlet Intergration at some point?
void Particle::update(float deltaTime)
{
    this->currentState.vy += this->currentState.gravity * deltaTime;
    this->currentState.y += this->currentState.vy * deltaTime;

    #ifdef DEBUG
    std::cout << "X, Y is : " << this->currentState.x << ", " << this->currentState.y << std::endl;
    #endif
}