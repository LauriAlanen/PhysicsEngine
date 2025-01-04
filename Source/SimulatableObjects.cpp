#include <SimulatableObjects.hpp>

#define DEBUG

Particle::Particle(int x, int y, float vx, float vy)
{
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
}

Particle::~Particle()
{

}

void Particle::update(float deltaTime)
{
    this->vy += this->gravity * deltaTime;
    this->y += vy * deltaTime;

    #ifdef DEBUG
    std::cout << "X, Y is : " << this->x << ", " << this->y << std::endl;
    #endif
}