#include <PhysicsObjects.hpp>

Particle::~Particle()
{

}

void Particle::update(float deltaTime)
{
    applyDrag(); // Apply drag before calculating forces

    // Calculate forces (including the drag forces)
    currentState.totalForce.x = currentState.mass * currentState.acceleration.x;
    currentState.totalForce.y = currentState.mass * (currentState.gravity + currentState.acceleration.y);

    // Update velocities based on acceleration
    currentState.velocity.x += (currentState.totalForce.x / currentState.mass) * deltaTime;
    currentState.velocity.y += (currentState.totalForce.y / currentState.mass) * deltaTime;

    // Update positions based on velocities
    currentState.position.x += currentState.velocity.x * deltaTime;
    currentState.position.y += currentState.velocity.y * deltaTime;

    // Update directional magnitudes
    magnitudes.right = (currentState.velocity.x > 0) ? std::abs(currentState.velocity.x) : 0;
    magnitudes.left = (currentState.velocity.x < 0) ? std::abs(currentState.velocity.x) : 0;
    magnitudes.down = (currentState.velocity.y > 0) ? std::abs(currentState.velocity.y) : 0;
    magnitudes.up = (currentState.velocity.y < 0) ? std::abs(currentState.velocity.y) : 0;
}

void Particle::applyDrag()
{
    float velocityMagnitude = currentState.velocity.magnitude();
    if (velocityMagnitude > 0) {
        // Calculate drag force vector
        float dragFactor = 0.5 * currentState.drag.dragCoefficient * currentState.drag.airDensity * currentState.drag.area;
        Vector2D dragForce = currentState.velocity.normalize() * (-dragFactor * velocityMagnitude * velocityMagnitude);
        applyForce(dragForce);
    }
}

void Particle::applyForce(Vector2D forceVector)
{
    currentState.totalForce += forceVector;
}