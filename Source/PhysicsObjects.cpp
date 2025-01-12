#include <PhysicsObjects.hpp>

Particle::Particle(BasicState currentState)
{
    this->currentState = currentState;
}

Particle::~Particle()
{

}

void Particle::updateEuler(float deltaTime)
{
    this->currentState.totalForce = glm::vec2(0, 0);
    applyDrag(); // Apply drag before calculating forces

    // Calculate forces (including the drag forces)
    this->currentState.totalForce.y += this->currentState.mass * (this->currentState.gravity + this->currentState.acceleration.y);
    this->currentState.totalForce.x += this->currentState.mass * this->currentState.acceleration.x;

    // Update velocities based on acceleration
    this->currentState.velocity += (this->currentState.totalForce / this->currentState.mass) * (deltaTime * SCALING_FACTOR);

    // Update positions based on velocities
    this->currentState.position += this->currentState.velocity * (deltaTime * SCALING_FACTOR);

    // calculateMagnitudes(); // Used for visualization
}

void Particle::updateVerlet(float deltaTime)
{
    this->currentState.totalForce = glm::vec2(0, 0);
    // applyDrag(); // Apply drag before calculating forces

    currentState.totalForce.y += currentState.gravity * currentState.mass;

    currentState.velocity = currentState.position - previousState.position;
    currentState.position = currentState.position + currentState.velocity + (currentState.totalForce / currentState.mass) * deltaTime * deltaTime;
    currentState.acceleration = {0 ,0};
}

void Particle::applyDrag()
{
    float velocityMagnitude = glm::length(this->currentState.velocity);
    spdlog::debug("Velocity Vector : {:.4f}", velocityMagnitude);

    if (velocityMagnitude > 0) {
        float dragFactor = 0.5 * this->currentState.drag.dragCoefficient * this->currentState.drag.airDensity * this->currentState.drag.area;
        glm::vec2 dragForce = glm::normalize(this->currentState.velocity) * (-dragFactor * velocityMagnitude * velocityMagnitude);
        applyForce(dragForce);
    }
}

void Particle::applyForce(glm::vec2 forceVector)
{
    this->currentState.totalForce += forceVector;
}

void Particle::calculateMagnitudes()
{
    magnitudes.right = (this->currentState.velocity.x > 0) ? std::abs(this->currentState.velocity.x) : 0;
    magnitudes.left = (this->currentState.velocity.x < 0) ? std::abs(this->currentState.velocity.x) : 0;
    magnitudes.down = (this->currentState.velocity.y > 0) ? std::abs(this->currentState.velocity.y) : 0;
    magnitudes.up = (this->currentState.velocity.y < 0) ? std::abs(this->currentState.velocity.y) : 0;
}