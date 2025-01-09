#include <PhysicsObjects.hpp>

Particle::~Particle()
{

}

void Particle::update_euler(float deltaTime)
{
    currentState.totalForce = Vector2D(0, 0);
    applyDrag(); // Apply drag before calculating forces

    // Calculate forces (including the drag forces)
    currentState.totalForce.y += currentState.mass * (currentState.gravity + currentState.acceleration.y);
    currentState.totalForce.x += currentState.mass * currentState.acceleration.x;

    // Update velocities based on acceleration
    currentState.velocity += (currentState.totalForce / currentState.mass) * (deltaTime * SCALING_FACTOR);

    // Update positions based on velocities
    currentState.position += currentState.velocity * (deltaTime * SCALING_FACTOR);

    calculateMagnitudes(); // Used for visualization

    previousState = currentState;  // Ensure the previousState is the same as currentState
}

void Particle::update_verlet(float deltaTime)
{
    currentState.totalForce = Vector2D(0, 0);
    
    applyDrag();
    currentState.totalForce.y += currentState.mass * currentState.gravity;
    
    currentState.position = currentState.position * 2.0f - previousState.position + (currentState.totalForce / currentState.mass) * deltaTime * deltaTime;

    previousState = currentState;  // Ensure the previousState is the same as currentState
}

void Particle::applyDrag()
{
    float velocityMagnitude = currentState.velocity.magnitude();
    spdlog::debug("Velocity Vector : {:.4f}", velocityMagnitude);

    if (velocityMagnitude > 0) {
        float dragFactor = 0.5 * currentState.drag.dragCoefficient * currentState.drag.airDensity * currentState.drag.area;
        Vector2D dragForce = currentState.velocity.normalize() * (-dragFactor * velocityMagnitude * velocityMagnitude);
        spdlog::debug("Applied dragForce {:.4f}, {:.4f} and unit vector is ({}, {})", dragForce.x, dragForce.y, currentState.velocity.normalize().x, currentState.velocity.normalize().y);
        applyForce(dragForce);
    }
}

void Particle::applyForce(Vector2D forceVector)
{
    currentState.totalForce += forceVector;
}

void Particle::calculateMagnitudes()
{
    magnitudes.right = (currentState.velocity.x > 0) ? std::abs(currentState.velocity.x) : 0;
    magnitudes.left = (currentState.velocity.x < 0) ? std::abs(currentState.velocity.x) : 0;
    magnitudes.down = (currentState.velocity.y > 0) ? std::abs(currentState.velocity.y) : 0;
    magnitudes.up = (currentState.velocity.y < 0) ? std::abs(currentState.velocity.y) : 0;
}