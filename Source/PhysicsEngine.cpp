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
            
            // resolveCollisions(object);
        }
        this->accumulator -= deltaTime;
        this->simulationTime += deltaTime;
    }

    const double interpolationFactor = this->accumulator / deltaTime;
    return interpolationFactor;
}

void PhysicsEngine::resolveCollisions(std::unique_ptr<PhysicsObject> &object)
{
    glm::vec2 halfBoundSize = boundingBox.position / 2.0f - glm::vec2(1.0f, 1.0f) * PARTICLE_SIZE;
    spdlog::debug("Halfbound size is ({:.4f},{:.4f}) when bounding box is ({:.4f}, {:.4f}) and {:.4f} {:.4f}",
    halfBoundSize.x, halfBoundSize.y, boundingBox.position.x, boundingBox.position.y, boundingBox.w, boundingBox.h);

    if (abs(object->currentState.position.x) > halfBoundSize.x)
    {
        object->currentState.position.x = halfBoundSize.x * glm::sign(object->currentState.position.x);
        object->currentState.velocity.x *= -1;
        spdlog::debug("New Position for x is {:.4f} and velocity {:.4f}", object->currentState.position.x, object->currentState.velocity.x);
    }
    
    if (abs(object->currentState.position.y) > halfBoundSize.y)
    {
        object->currentState.position.y = halfBoundSize.y * glm::sign(object->currentState.position.y);
        object->currentState.velocity.y *= -1;
        spdlog::debug("New Position for y is {:.4f} and velocity {:.4f}", object->currentState.position.y, object->currentState.velocity.y);
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
