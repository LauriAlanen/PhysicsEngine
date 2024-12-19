#include <PhysicsEngine.hpp>

#define DEBUG 1

PhysicsEngine::PhysicsEngine(float fps)
{
    this->timestep = (1.0f / fps);
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
    while (this->accumulator >= this->timestep)
    {
        for (auto& object : this->simulatableObjects)
        {
            #ifdef DEBUG
            std::cout << "Last Update Was: " << deltaTime << "\n";
            #endif
            object->update(this->timestep);
        }
        accumulator -= this->timestep;
    }

}

void PhysicsEngine::addSimulatableObject(std::unique_ptr<SimulatableObject> object)
{
    this->simulatableObjects.push_back(std::move(object));
}
