#include <SimulatableObjects.hpp>

// #define DEBUG

Particle::~Particle()
{

}

void Particle::update(float deltaTime)
{
    this->currentState.vy += this->currentState.gravity * deltaTime;
    this->currentState.y += this->currentState.vy * deltaTime;

    spdlog::debug("Updating particle: currentState.y = {}, currentState.vy = {:.4f}, gravity = {:.4f}, deltaTime = {:.4f}",
                  this->currentState.y, this->currentState.vy, this->currentState.gravity, deltaTime);
}