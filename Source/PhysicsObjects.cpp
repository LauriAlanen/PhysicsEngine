#include <PhysicsObjects.hpp>

Particle::~Particle()
{

}

void Particle::update_euler(float deltaTime)
{
    this->currentState.totalForce = Vector2D(0, 0);
    applyDrag(); // Apply drag before calculating forces

    // Calculate forces (including the drag forces)
    this->currentState.totalForce.y += this->currentState.mass * (this->currentState.gravity + this->currentState.acceleration.y);
    this->currentState.totalForce.x += this->currentState.mass * this->currentState.acceleration.x;

    // Update velocities based on acceleration
    this->currentState.velocity += (this->currentState.totalForce / this->currentState.mass) * (deltaTime * SCALING_FACTOR);

    // Update positions based on velocities
    this->currentState.position += this->currentState.velocity * (deltaTime * SCALING_FACTOR);

    calculateMagnitudes(); // Used for visualization
}

void Particle::update_verlet(float deltaTime)
{
    // Calculate initial acceleration
    this->currentState.acceleration = this->currentState.totalForce / this->currentState.mass;

    // Update position using current velocity and acceleration
    this->currentState.position += this->currentState.velocity * deltaTime +
                             (this->currentState.acceleration * 0.5f * deltaTime * deltaTime);

    // Intermediate velocity update
    this->currentState.velocity += this->currentState.velocity + this->currentState.acceleration * 0.5f * deltaTime;

    // Recalculate forces and acceleration based on new position
    this->currentState.totalForce = Vector2D(0, 0); // Reset total force
    applyDrag(); // Apply drag or other forces
    this->currentState.totalForce.x += this->currentState.mass * this->currentState.acceleration.x;
    this->currentState.totalForce.y += this->currentState.mass * (this->currentState.acceleration.y + this->currentState.gravity);

    this->currentState.acceleration = this->currentState.totalForce / this->currentState.mass;

    this->currentState.velocity += this->currentState.acceleration * 0.5f * deltaTime;
}


void Particle::applyDrag()
{
    float velocityMagnitude = this->currentState.velocity.magnitude();
    spdlog::debug("Velocity Vector : {:.4f}", velocityMagnitude);

    if (velocityMagnitude > 0) {
        float dragFactor = 0.5 * this->currentState.drag.dragCoefficient * this->currentState.drag.airDensity * this->currentState.drag.area;
        Vector2D dragForce = this->currentState.velocity.normalize() * (-dragFactor * velocityMagnitude * velocityMagnitude);
        spdlog::debug("Applied dragForce {:.4f}, {:.4f} and unit vector is ({}, {})", dragForce.x, dragForce.y, this->currentState.velocity.normalize().x, this->currentState.velocity.normalize().y);
        applyForce(dragForce);
    }
}

void Particle::applyForce(Vector2D forceVector)
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