#include <PhysicsEngine.hpp>

PhysicsEngine::PhysicsEngine(float fps)
{
    this->previousTime = SDL_GetTicks();
    this->timestep = (1.0f / fps) * 1000;
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::update()
{
    double currentTime = SDL_GetTicks();
    const double maxDeltaTime = 100.0f;
    this->deltaTime = std::min(currentTime - previousTime, maxDeltaTime);
    this->previousTime = currentTime;

    this->accumulator += this->deltaTime; 

    // TODO: After the basic simulatiion is running with a fixed timestep 
    // Try implementing render interpolation https://gafferongames.com/post/fix_your_timestep/
    while (this->accumulator >= this->timestep)
    {
        for (auto& object : this->simulatableObjects)
        {
            std::cout << "Last Update Was: " << this->deltaTime << "\n";
            //std::cout << "Tick was: " << SDL_GetTicks() << "\n";
            object->update(this->timestep);
        }
        this->accumulator -= this->timestep;
    }

}

void PhysicsEngine::addSimulatableObject(std::unique_ptr<SimulatableObject> object)
{
    this->simulatableObjects.push_back(std::move(object));
}
