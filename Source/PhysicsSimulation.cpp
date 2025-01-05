#include <PhysicsSimulation.hpp>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time() to seed the random number generator

#define SIMULATION_FPS 60.0f
// #define DEBUG

int main() 
{
    PhysicsRenderer renderer("Physics Renderer");

    Bounds simulationBounds(0, 0, renderer.width, renderer.height);
	PhysicsEngine engine(SIMULATION_FPS, simulationBounds);

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    
    // Add 100 particles at random positions
    for (int i = 0; i < 10000; ++i) 
    {
        // Generate random positions within some range
        double randomX = rand() % (renderer.width * 2);   // Random X position (width of screen)
        double randomY = rand() % (renderer.height);  // Random Y position (height of screen)
        
        // Create a new Particle with random positions (and zero velocity)
        engine.addSimulatableObject(std::make_unique<Particle>(randomX, randomY, 1.0, 0.0, 0.0));
    }

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        double interpolationFactor = engine.update(); // Update physics and return the interpolationFactor
        renderer.renderObjects(engine.getSimulatableObjects(), interpolationFactor); // Now update the render with new positions using interpolationFactor
        renderer.present();   
    }

    return 0;
}
