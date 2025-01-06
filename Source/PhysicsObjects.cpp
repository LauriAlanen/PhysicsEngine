#include <PhysicsObjects.hpp>

Particle::~Particle()
{

}

void Particle::update(float deltaTime)
{
    applyDrag(); // Apply drag before calculating forces

    // Calculate forces (including the drag forces)
    currentState.Fx = currentState.mass * currentState.ax;
    currentState.Fy = currentState.mass * (currentState.gravity + currentState.ay);

    // Update velocities based on acceleration
    currentState.vx += (currentState.Fx / currentState.mass) * deltaTime;
    currentState.vy += (currentState.Fy / currentState.mass) * deltaTime;

    // Update positions based on velocities
    currentState.x += currentState.vx * deltaTime;
    currentState.y += currentState.vy * deltaTime;

    // Update directional magnitudes
    magnitudes.right = (currentState.vx > 0) ? std::abs(currentState.vx) : 0;
    magnitudes.left = (currentState.vx < 0) ? std::abs(currentState.vx) : 0;
    magnitudes.down = (currentState.vy > 0) ? std::abs(currentState.vy) : 0;
    magnitudes.up = (currentState.vy < 0) ? std::abs(currentState.vy) : 0;

    spdlog::debug("Updating particle: x = {:.4f}, y = {:.4f}, vx = {:.4f}, vy = {:.4f}, ax = {:.4f}, ay = {:.4f}, mass = {:.4f}, gravity = {:.4f}, deltaTime = {:.4f}",
                  currentState.x, currentState.y, currentState.vx, currentState.vy, 
                  currentState.ax, currentState.ay, currentState.mass, BasicState::gravity, deltaTime);
}

void Particle::applyDrag()
{
    float velocityVector = sqrt(currentState.vx * currentState.vx + currentState.vy * currentState.vy);
    if (velocityVector > 0) 
    {
        // Calculate drag force components based on velocity, not position
        currentState.drag.xFdrag = 0.5 * currentState.drag.dragCoefficient * currentState.drag.airDensity * currentState.area * currentState.vx * currentState.vx;
        currentState.drag.yFdrag = 0.5 * currentState.drag.dragCoefficient * currentState.drag.airDensity * currentState.area * currentState.vy * currentState.vy;

        // Apply drag force (drag always opposes velocity, so it's subtracted from acceleration)
        currentState.ax -= copysign(currentState.drag.xFdrag, -currentState.vx) / currentState.mass;
        currentState.ay -= copysign(currentState.drag.yFdrag, -currentState.vy) / currentState.mass;
    }
}
