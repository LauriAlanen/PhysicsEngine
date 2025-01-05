#include <SimulatableObjects.hpp>

// #define DEBUG

Particle::~Particle()
{

}

void Particle::update(float deltaTime)
{
    spdlog::debug("Updating particle: currentState.y = {}, currentState.vy = {:.4f}, gravity = {:.4f}, deltaTime = {:.4f}",
                  this->currentState.y, this->currentState.vy, this->currentState.gravity, deltaTime);

    this->currentState.vy += this->currentState.gravity * deltaTime;
    spdlog::debug("Updated vy = {}", this->currentState.vy);

    this->currentState.y += this->currentState.vy * deltaTime;
    spdlog::debug("Updated y = {}", this->currentState.y);
}