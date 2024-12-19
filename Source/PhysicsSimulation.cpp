#include <PhysicsRenderer.hpp>
#include <PhysicsEngine.hpp>
#include <SimulatableObjects.hpp>

#define SIMULATION_FPS 60.0f

int main() {
    Uint64 now, last;

    PhysicsRenderer renderer("Physics Renderer", 1200, 900);
	PhysicsEngine engine(SIMULATION_FPS);

	engine.addSimulatableObject(std::make_unique<Particle>(20, 100));

    bool running = true;
    SDL_Event event;

    while (running) {
        now = SDL_GetPerformanceCounter();
        last = now;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        double frameTime = (SDL_GetPerformanceCounter() - now) / (double)SDL_GetPerformanceFrequency();
        if (frameTime < engine.timestep)
        {
            SDL_Delay(engine.timestep - frameTime);
        }

        engine.update();
        renderer.present();   
    }

    return 0;
}
