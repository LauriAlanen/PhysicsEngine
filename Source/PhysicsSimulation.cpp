#include <PhysicsRenderer.hpp>
#include <PhysicsEngine.hpp>
#include <SimulatableObjects.hpp>

#define SIMULATION_FPS 60.0f

int main() {

    PhysicsRenderer renderer("Physics Renderer", 1000, 800);
	PhysicsEngine engine(SIMULATION_FPS);

	engine.addSimulatableObject(std::make_unique<Particle>(100, 500));
	engine.addSimulatableObject(std::make_unique<Particle>(200, 1000));
	engine.addSimulatableObject(std::make_unique<Particle>(300, 20));
	engine.addSimulatableObject(std::make_unique<Particle>(400, 300));

    bool running = true;
    SDL_Event event;
    Uint64 now;

    while (running) {
        now = SDL_GetPerformanceCounter();

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        double frameTime = (SDL_GetPerformanceCounter() - now) / (double)SDL_GetPerformanceFrequency();
        if (frameTime < (engine.timestep))
        {
            SDL_Delay((engine.timestep - frameTime) * 1000); // Convert to ms for SDL_Delay
        }

        engine.update(); // Update only physics
        renderer.renderObjects(engine.getSimulatableObjects()); // Now update the render with new positions
        renderer.present();   
    }

    return 0;
}
