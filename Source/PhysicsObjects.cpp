#include <PhysicsObjects.hpp>

Particle::~Particle()
{

}

void Particle::update(float deltaTime)
{
    this->currentState.Fx = this->currentState.mass * this->currentState.ax;
    this->currentState.Fy = this->currentState.mass * (this->currentState.gravity + this->currentState.ay);

    spdlog::debug("Fx : {:.4f} and Fy : {:.4f}, ax : {:.4f} and ay : {:.4f}, vx : {:.4f} and vy : {:.4f}", 
    this->currentState.Fx, this->currentState.Fy, this->currentState.ax, this->currentState.ay, this->currentState.vx, this->currentState.vy);

    this->currentState.vy += this->currentState.Fy / this->currentState.mass * deltaTime;
    this->currentState.y += this->currentState.vy * deltaTime;

    this->currentState.vx += this->currentState.ax * deltaTime;
    this->currentState.x += this->currentState.vx * deltaTime;

    if (this->currentState.vx > 0)
        this->magnitudes.right = std::abs(currentState.vx);
    else
        this->magnitudes.left = std::abs(currentState.vx);

    if (this->currentState.vy > 0)
        this->magnitudes.down = std::abs(currentState.vy);
    else
        this->magnitudes.up = std::abs(currentState.vy);

    spdlog::trace("Updating particle: x = {:.4f}, y = {:.4f}, vx = {:.4f}, vy = {:.4f}, ax = {:.4f}, ay = {:.4f}, mass = {:.4f}, gravity = {:.4f}, deltaTime = {:.4f}",
                this->currentState.x, this->currentState.y, this->currentState.vx, this->currentState.vy, this->currentState.ax, this->currentState.ay, 
                this->currentState.mass, BasicState::gravity, deltaTime);
}