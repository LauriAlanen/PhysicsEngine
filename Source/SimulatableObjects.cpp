#include <SimulatableObjects.hpp>

Particle::Particle(float position, float velocity)
{
    this->position = position;
    this->velocity = velocity;
}
Particle::~Particle()
{

}

void Particle::update(float deltaTime)
{
    this->velocity += this->gravity * deltaTime;
    this->position += this->velocity * deltaTime;
}