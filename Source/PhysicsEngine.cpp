#include <PhysicsEngine.hpp>

PhysicsEngine::PhysicsEngine(float fps)
{
    this->deltaTime = (1.0f / fps);
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
            
            #ifdef EULER
            object->updateEuler(this->deltaTime);
            #endif
            
            #ifdef VERLET
            object->updateVerlet(this->deltaTime);
            #endif
            
            resolveCollisions(object);
            object->previousState = object->currentState;
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
                                                    boundingBox.position.x + boundingBox.size.x - PARTICLE_SIZE);
    object->currentState.position.y = std::clamp(object->currentState.position.y, boundingBox.position.y + PARTICLE_SIZE, 
                                                    boundingBox.position.y + boundingBox.size.x - PARTICLE_SIZE);
    // Optionally, reverse the velocity if the objectangle is trying to move out of bounds
    if (object->currentState.position.x - PARTICLE_SIZE == boundingBox.position.x || 
                object->currentState.position.x == boundingBox.position.x + boundingBox.size.x - PARTICLE_SIZE) {
        object->currentState.velocity.x *= -1; // Reverse velocity on X-axis if hitting the left or right side
        object->currentState.acceleration.x = 0;
    }
    if (object->currentState.position.y - PARTICLE_SIZE == boundingBox.position.y ||
                object->currentState.position.y == boundingBox.position.y + boundingBox.size.y - PARTICLE_SIZE) {
        object->currentState.velocity.y *= -1; // Reverse velocity on Y-axis if hitting the top or bottom side
        object->currentState.acceleration.y = 0;
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

void PhysicsEngine::setBoundingBox(BoundingBox boundingBox)
{
    this->boundingBox = boundingBox;
}

void PhysicsEngine::modifyBoundingBox(glm::vec2 position, glm::vec2 size)
{
    this->boundingBox.position = position;
    this->boundingBox.size = size;
}

BasicState PhysicsEngine::generateRandomParticle(glm::vec2 position)
{
    BasicState particle;

    particle.position.x = position.x;
    particle.position.y = position.y;

    // Randomize velocity (e.g., velocity between -10 and 10 for both x and y components)
    particle.velocity.x = (rand() % 21 - 10); // Random velocity between -10 and 10
    particle.velocity.y = (rand() % 21 - 10); // Random velocity between -10 and 10

    // Randomize acceleration (e.g., acceleration between -5 and 5 for both x and y components)
    particle.acceleration.x = (rand() % 11 - 5); // Random acceleration between -5 and 5
    particle.acceleration.y = (rand() % 11 - 5); // Random acceleration between -5 and 5

    // Drag properties (constant or slightly varied)
    particle.drag.airDensity = 1.225; // Standard air density
    particle.drag.dragCoefficient = 0.47; // Drag coefficient for a sphere
    particle.drag.area = 1 + (rand() % 10) / 10.0f; // Random area between 1.0 and 2.0

    // Randomize mass
    particle.mass = 50 + rand() % 101; // Random mass between 50 and 150
    
    return particle;
}