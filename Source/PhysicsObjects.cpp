#include <PhysicsObjects.hpp>

Particle::~Particle()
{

}

void Particle::update(float deltaTime)
{
    this->currentState.Fx = this->currentState.mass * this->currentState.ax;
    this->currentState.Fy = this->currentState.mass * this->currentState.gravity;

    if (this->currentState.Fx > 0)
        this->magnitudes.right = std::abs(currentState.Fx);
    else
        this->magnitudes.left = std::abs(currentState.Fx);

    if (this->currentState.Fy > 0)
        this->magnitudes.up = std::abs(currentState.Fy);
    else
        this->magnitudes.down = std::abs(currentState.Fy);

    this->currentState.vy += this->currentState.Fy / this->currentState.mass * deltaTime;
    this->currentState.y += this->currentState.vy * deltaTime;

    this->currentState.vx += this->currentState.ax * deltaTime;
    this->currentState.x += this->currentState.vx * deltaTime;

    spdlog::trace("Updating particle: x = {:.4f}, y = {:.4f}, vx = {:.4f}, vy = {:.4f}, ax = {:.4f}, ay = {:.4f}, mass = {:.4f}, gravity = {:.4f}, deltaTime = {:.4f}",
                this->currentState.x, this->currentState.y, this->currentState.vx, this->currentState.vy, this->currentState.ax, this->currentState.ay, 
                this->currentState.mass, BasicState::gravity, deltaTime);
}