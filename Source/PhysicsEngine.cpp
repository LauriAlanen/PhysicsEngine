#include <PhysicsEngine.hpp>

#define DEBUG

PhysicsEngine::PhysicsEngine(float fps, Bounds simulationBounds)
{
    this->deltaTime = (1.0f / fps);
    this->simulationBounds = simulationBounds;
    this->previousTime = SDL_GetPerformanceCounter();
}

PhysicsEngine::~PhysicsEngine()
{
}

double PhysicsEngine::update()
{
    this->newTime = SDL_GetPerformanceCounter();
    
    double frameTime;
    frameTime = (this->newTime - this->previousTime) / (double)SDL_GetPerformanceFrequency();
    if (frameTime > 0.25f)
    {
        frameTime = 0.25f;
        spdlog::warn("Experiencing slowdown. Max frame time reached: {:.4f} seconds.", frameTime);
    }
    this->previousTime = this->newTime;

    this->accumulator += frameTime; 

    if (this->simulationTime == 0.0) // Handle edge case so on first iteration previous and current states are the same so interpolation does work correctly
    {
        for (auto& object : this->simulatableObjects) 
        {
            object->previousState = object->currentState;  // Ensure the previousState is the same as currentState
            spdlog::debug("First iteration: Synchronizing previousState with currentState for object. Position: ({}, {}), Velocity: ({:.4f}, {:.4f})",
                          object->currentState.x, object->currentState.y, 
                          object->currentState.vx, object->currentState.vy);
        }
    }

    while (this->accumulator >= this->deltaTime)
    {
        // Integrate
        for (auto& object : this->simulatableObjects) 
        {
            object->previousState = object->currentState;
            object->update(this->deltaTime);
            checkBounds(object);
            spdlog::debug("Object updated. Position: ({}, {}), Velocity: ({:.4f}, {:.4f})", 
                          object->currentState.x, object->currentState.y, 
                          object->currentState.vx, object->currentState.vy);
        }
        this->accumulator -= deltaTime;
        this->simulationTime += deltaTime;
        spdlog::debug("Updated object states. Accumulator: {:.4f}, Simulation time: {:.4f}", this->accumulator, this->simulationTime);
    }

    const double interpolationFactor = this->accumulator / deltaTime;
    spdlog::debug("Interpolation factor: {:.4f}", interpolationFactor);
    spdlog::debug("Simulation time: {}", this->simulationTime);

    return interpolationFactor;
}

void PhysicsEngine::checkBounds(std::unique_ptr<SimulatableObject> &object)
{
    bool positionChanged = false;
    
    if (object->currentState.y > this->simulationBounds.y_max || object->currentState.y <= this->simulationBounds.y_min)
    {
        object->currentState.vy = 0;
        positionChanged = true;
        spdlog::debug("Object out of bounds (Y-axis). Velocity set to 0.");
    }

    if (object->currentState.x > this->simulationBounds.x_max || object->currentState.x <= this->simulationBounds.x_min)
    {
        object->currentState.vx = 0;
        positionChanged = true;
        spdlog::debug("Object out of bounds (X-axis). Velocity set to 0.");
    }

    if (positionChanged)
    {
        spdlog::debug("Object position and velocity updated after bounds check.");
    }
}

void PhysicsEngine::addSimulatableObject(std::unique_ptr<SimulatableObject> object)
{
    this->simulatableObjects.push_back(std::move(object));
    spdlog::debug("Simulatable object added. Total objects: {}", this->simulatableObjects.size());

}

std::vector<std::unique_ptr<SimulatableObject>>& PhysicsEngine::getSimulatableObjects()
{
    spdlog::debug("Returning simulatable objects. Total objects: {}", this->simulatableObjects.size());
    return this->simulatableObjects;
}
