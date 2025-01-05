#include <PhysicsEngine.hpp>

// #define DEBUG

PhysicsEngine::PhysicsEngine(float fps, Bounds simulationBounds)
{
    this->deltaTime = (1.0f / fps);
    this->simulationBounds = simulationBounds;
}

PhysicsEngine::~PhysicsEngine()
{
    this->currentTime = SDL_GetPerformanceCounter();
}

double PhysicsEngine::update()
{
    Uint64 newTime = SDL_GetPerformanceCounter();
    
    double frameTime;
    frameTime = (newTime - this->currentTime) / (double)SDL_GetPerformanceFrequency();
    if (frameTime > 0.25f)
    {
        frameTime = 0.25f;
    }
    this->currentTime = newTime;

    this->accumulator += frameTime; 

    while (this->accumulator >= deltaTime)
    {
        for (auto& object : this->simulatableObjects)
        {
            object->previousState = object->currentState;
            object->update(this->deltaTime);
            checkBounds(object);
        }
        this->accumulator -= deltaTime;
        this->simulationTime += deltaTime;
    }

    const double interpolationFactor = this->accumulator / deltaTime;

    #ifdef DEBUG
    std::cout << "Simulationtime : " << this->simulationTime << std::endl;
    std::cout << "Interpolation factor is : " << interpolationFactor << std::endl;
    #endif

    return interpolationFactor;
}

void PhysicsEngine::checkBounds(std::unique_ptr<SimulatableObject> &object)
{
    if (object->currentState.y > this->simulationBounds.y_max || object->currentState.y <= this->simulationBounds.y_min)
    {
        object->currentState.vy = 0;
    }

    else if (object->currentState.x > this->simulationBounds.x_max || object->currentState.x <= this->simulationBounds.x_min)
    {
        object->currentState.vx = 0;
    }
}

void PhysicsEngine::addSimulatableObject(std::unique_ptr<SimulatableObject> object)
{
    this->simulatableObjects.push_back(std::move(object));
}

std::vector<std::unique_ptr<SimulatableObject>>& PhysicsEngine::getSimulatableObjects()
{
    return this->simulatableObjects;
}
