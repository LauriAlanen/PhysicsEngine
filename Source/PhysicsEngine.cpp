#include <PhysicsEngine.hpp>

#define DEBUG

PhysicsEngine::PhysicsEngine(float fps, Bounds simulationBounds)
{
    this->timestep = (1.0f / fps);
    this->simulationBounds = simulationBounds;
}

PhysicsEngine::~PhysicsEngine()
{
    this->previousTime = SDL_GetPerformanceCounter();
}

void PhysicsEngine::update()
{
    Uint64 currentTime = SDL_GetPerformanceCounter();
    const double maxDeltaTime = 0.1f;
    double deltaTime;
    
    deltaTime = (currentTime - previousTime) / (double)SDL_GetPerformanceFrequency();
    deltaTime = std::min(deltaTime, maxDeltaTime);
    previousTime = currentTime;

    this->accumulator += deltaTime; 

    // TODO: After the basic simulatiion is running with a fixed timestep 
    // Try implementing render interpolation https://gafferongames.com/post/fix_your_timestep/
    while (this->accumulator >= deltaTime)
    {
        for (auto& object : this->simulatableObjects)
        {
            object->update(this->timestep);
            checkBounds(object);
        }
        this->accumulator -= deltaTime;
        this->simulationTime += deltaTime;
    }
    #ifdef DEBUG
    std::cout << "Simulationtime : " << this->simulationTime << std::endl;
    #endif

}

void PhysicsEngine::checkBounds(std::unique_ptr<SimulatableObject> &object)
{
    if (object->y > this->simulationBounds.y_max || object->y <= this->simulationBounds.y_min)
    {
        #ifdef DEBUG
        std::cout << "Object is out of y bounds!!!" << std::endl;
        #endif
        object->vy = 0;
    }

    else if (object->x > this->simulationBounds.x_max || object->x <= this->simulationBounds.x_min)
    {
        #ifdef DEBUG
        std::cout << "Object is out of x bounds!!!" << std::endl;
        #endif
        object->vx = 0;
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
