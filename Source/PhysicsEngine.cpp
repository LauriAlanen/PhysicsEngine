#include <PhysicsEngine.hpp>

PhysicsEngine::PhysicsEngine(float fps, BoundingBox boundingBox)
{
    this->deltaTime = (1.0f / fps);
    this->boundingBox = boundingBox;
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

    while (this->accumulator >= this->deltaTime)
    {
        for (auto& object : this->physicsObjects) 
        {
            object->previousState = object->currentState;
            
            #ifdef EULER
            object->update_euler(this->deltaTime);
            #endif
            
            #ifdef VERLET
            object->update_verlet(this->deltaTime);
            #endif
            
            resolveCollisions(object);
        }
        this->accumulator -= deltaTime;
        this->simulationTime += deltaTime;
    }

    const double interpolationFactor = this->accumulator / deltaTime;
    return interpolationFactor;
}

void PhysicsEngine::resolveCollisions(std::unique_ptr<PhysicsObject> &object)
{
    object->currentState.position.x = std::clamp(object->currentState.position.x, boundingBox.position.x + PARTICLE_SIZE, 
                                                    boundingBox.position.x + boundingBox.w - PARTICLE_SIZE);
    object->currentState.position.y = std::clamp(object->currentState.position.y, boundingBox.position.y + PARTICLE_SIZE, 
                                                    boundingBox.position.y + boundingBox.w - PARTICLE_SIZE);
    // Optionally, reverse the velocity if the objectangle is trying to move out of bounds
    if (object->currentState.position.x - PARTICLE_SIZE == boundingBox.position.x || 
                object->currentState.position.x == boundingBox.position.x + boundingBox.w - PARTICLE_SIZE) {
        object->currentState.velocity.x *= -1; // Reverse velocity on X-axis if hitting the left or right side
    }
    if (object->currentState.position.y - PARTICLE_SIZE == boundingBox.position.y ||
                object->currentState.position.y == boundingBox.position.y + boundingBox.h - PARTICLE_SIZE) {
        object->currentState.velocity.y *= -1; // Reverse velocity on Y-axis if hitting the top or bottom side
    }
}

void PhysicsEngine::addPhysicsObject(std::unique_ptr<PhysicsObject> object)
{
    this->physicsObjects.push_back(std::move(object));
    spdlog::trace("Simulatable object added. Total objects: {}", this->physicsObjects.size());
}

std::vector<std::unique_ptr<PhysicsObject>>& PhysicsEngine::getPhysicsObjects()
{
    spdlog::trace("Returning simulatable objects. Total objects: {}", this->physicsObjects.size());
    return this->physicsObjects;
}

int PhysicsEngine::getPhysicsObjectCount()
{
    return this->physicsObjects.size();
}
