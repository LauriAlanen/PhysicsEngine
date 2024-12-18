#include <PhysicsEngine.hpp>

PhysicsEngine::PhysicsEngine(float fps)
{
    this->previousTime = SDL_GetTicks();
    this->timestep = 1.0f / fps;
}

PhysicsEngine::~PhysicsEngine()
{
}

void PhysicsEngine::update()
{
    float currentTime = SDL_GetTicks();
    this->deltaTime = currentTime - previousTime;

    this->accumulator += this->deltaTime; 

    while (this->accumulator >= this->timestep)
    {
        for (auto& object : this->simulatableObjects)
        {
            std::cout << "Deltatime Was Updated: " << this->deltaTime << "\n";
            std::cout << "Tick was: " << SDL_GetTicks() << "\n";
            object->update(this->timestep);
        }
        this->accumulator -= this->timestep;
    }

    this->previousTime = currentTime;
}

void PhysicsEngine::addSimulatableObject(std::unique_ptr<SimulatableObject> object)
{
    this->simulatableObjects.push_back(std::move(object));
}
