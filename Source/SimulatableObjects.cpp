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
    this->x_coordinate = position;
    this->y_coordinate = velocity;
    std::cout << "X is : " << this->x_coordinate << std::endl;
    std::cout << "Y is : " << this->y_coordinate << std::endl;
}