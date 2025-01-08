#include <PhysicsSimulation.hpp>

#define SIMULATION_FPS 300.0f

int main() 
{
    spdlog::set_level(spdlog::level::info); // Set global log level to debug
    // auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/debug_log.txt");
    // spdlog::set_default_logger(file_logger);

    spdlog::trace("Initializing Physics Renderer...");
    PhysicsRenderer renderer("Physics Renderer");

    Bounds simulationBounds(0, 0, renderer.width, renderer.height);
    spdlog::trace("Simulation bounds set: x_min = {}, y_min = {}, x_max = {}, y_max = {}",
                  simulationBounds.x_min, simulationBounds.y_min, simulationBounds.x_max, simulationBounds.y_max);


	PhysicsEngine engine(SIMULATION_FPS, simulationBounds);
    spdlog::trace("Physics Engine initialized with FPS: {}", SIMULATION_FPS);

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    
    for (int i = 0; i < 100; ++i) {
        BasicState particle;

        // Randomize position (within bounds)
        particle.position.x = rand() % renderer.width; // Random x between 0 and renderer width
        particle.position.y = rand() % renderer.height; // Random y between 0 and renderer height

        // Randomize velocity
        particle.velocity.x = (rand() % 200 - 100) / 10.0f; // Random velocity x between -10.0 and 10.0
        particle.velocity.y = (rand() % 200 - 100) / 10.0f; // Random velocity y between -10.0 and 10.0

        // Randomize acceleration
        particle.acceleration.x = (rand() % 100 - 50) / 10.0f; // Random acceleration x between -5.0 and 5.0
        particle.acceleration.y = (rand() % 100 - 50) / 10.0f; // Random acceleration y between -5.0 and 5.0

        // Drag properties (constant or slightly varied)
        particle.drag.airDensity = 1.225; // Standard air density
        particle.drag.dragCoefficient = 0.47; // Drag coefficient for a sphere
        particle.drag.area = 1 + (rand() % 10) / 10.0f; // Random area between 1.0 and 2.0

        // Randomize mass
        particle.mass = 50 + rand() % 101; // Random mass between 50 and 150

        // Add the particle to the physics engine
        engine.addPhysicsObject(std::make_unique<Particle>(particle));
    }

    bool running = true;
    SDL_Event event;

    auto lastTime = std::chrono::high_resolution_clock::now(); 
    int frameCount = 0;
    float fps = 0.0f;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) 
            {
                running = false;
            }
        }

        spdlog::trace("Updating physics engine...");
        double interpolationFactor = engine.update(); // Update physics and return the interpolationFactor
        
        spdlog::trace("Rendering objects...");
        renderer.renderObjects(engine.getPhysicsObjects(), interpolationFactor); // Now update the render with new positions using interpolationFactor
        renderer.present();  

        frameCount++;
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count();

        if (duration >= 1000) { // Update FPS every second
            fps = frameCount / (duration / 1000.0f);
            frameCount = 0;
            lastTime = currentTime;
            spdlog::info("FPS: {:.2f}", fps); // Log FPS
        }
    }

    spdlog::trace("Simulation finished.");
    return 0;
}
