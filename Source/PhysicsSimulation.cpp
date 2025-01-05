#include <PhysicsSimulation.hpp>

#define SIMULATION_FPS 500.0f

int main() 
{
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
    auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/debug_log.txt");
    spdlog::set_default_logger(file_logger);

    spdlog::debug("Initializing Physics Renderer...");
    PhysicsRenderer renderer("Physics Renderer");

    Bounds simulationBounds(0, 0, renderer.width, renderer.height);
    spdlog::debug("Simulation bounds set: x_min = {}, y_min = {}, x_max = {}, y_max = {}",
                  simulationBounds.x_min, simulationBounds.y_min, simulationBounds.x_max, simulationBounds.y_max);


	PhysicsEngine engine(SIMULATION_FPS, simulationBounds);
    spdlog::debug("Physics Engine initialized with FPS: {}", SIMULATION_FPS);

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    
    // Add particles at random positions
    for (int i = 0; i < 1; ++i) 
    {
        // Generate random positions within some range
        double randomX = 500;   // Random X position (width of screen)
        double randomY = 500;  // Random Y position (height of screen)
        
        spdlog::debug("Creating particle {} with random position: x = {}, y = {}", i + 1, randomX, randomY);
        engine.addSimulatableObject(std::make_unique<Particle>(randomX, randomY, 0.0, 0.0, 0.0));
    }

    bool running = true;
    SDL_Event event;

    spdlog::debug("Starting a new simulation...");
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        spdlog::debug("Updating physics engine...");
        double interpolationFactor = engine.update(); // Update physics and return the interpolationFactor
        
        spdlog::debug("Rendering objects...");
        renderer.renderObjects(engine.getSimulatableObjects(), interpolationFactor); // Now update the render with new positions using interpolationFactor
        renderer.present();   
    }

    spdlog::debug("Simulation finished.");
    return 0;
}
