#include <PhysicsRenderer.hpp>
#include <PhysicsEngine.hpp>
#include <SimulatableObjects.hpp>

#define SIMULATION_FPS 60.0f

int main() {
    PhysicsRenderer renderer("Physics Renderer", 1200, 900);
	PhysicsEngine engine(SIMULATION_FPS);

	engine.addSimulatableObject(std::make_unique<Particle>(20, 100));

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        renderer.present();
		engine.update();
    }

    return 0;
}
