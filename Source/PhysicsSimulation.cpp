#include <PhysicsSimulation.hpp>

#define SIMULATION_FPS 100.0f

int main() 
{
    PhysicsRenderer renderer("Physics Renderer");

    Bounds simulationBounds(0, 0, renderer.width, renderer.height);
	PhysicsEngine engine(SIMULATION_FPS, simulationBounds);

	engine.addSimulatableObject(std::make_unique<Particle>(500, 800, 0, 0));
	engine.addSimulatableObject(std::make_unique<Particle>(400, 1000, 0, 0));
	engine.addSimulatableObject(std::make_unique<Particle>(1000, 500, 0, 0));

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        engine.update(); // Update only physics
        renderer.renderObjects(engine.getSimulatableObjects()); // Now update the render with new positions
        renderer.present();   
    }

    return 0;
}
