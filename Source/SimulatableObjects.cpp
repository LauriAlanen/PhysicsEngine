#include <SimulatableObjects.hpp>

Particle::~Particle()
{

}

void Particle::update(float deltaTime)
{
    this->currentState.vy += (this->currentState.gravity) * deltaTime;
    this->currentState.y += this->currentState.vy * deltaTime;
    this->currentState.vx += this->currentState.ax * deltaTime;
    this->currentState.x += this->currentState.vx * deltaTime;

    spdlog::debug("Updating particle: x = {:.4f}, y = {:.4f}, vx = {:.4f}, vy = {:.4f}, ax = {:.4f}, ay = {:.4f}, mass = {:.4f}, gravity = {:.4f}, deltaTime = {:.4f}",
                this->currentState.x, this->currentState.y, this->currentState.vx, this->currentState.vy, this->currentState.ax, this->currentState.ay, 
                this->currentState.mass, BasicState::gravity, deltaTime);

}