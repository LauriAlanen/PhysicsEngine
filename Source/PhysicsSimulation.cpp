#include <PhysicsSimulation.hpp>

#define SIMULATION_FPS 200.0f

int main() 
{
    spdlog::set_level(spdlog::level::debug); // Set global log level to debug
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
    
    // Add particles at random positions
    BasicState particleState;
    particleState.position.x = 800;
    particleState.position.y = renderer.height - 200;
    particleState.velocity.y = 10;
    particleState.velocity.x = 5;
    particleState.acceleration.x = 0;
    particleState.acceleration.y = 0;
    particleState.drag.airDensity = 1.225;
    particleState.drag.dragCoefficient = 0.47;
    particleState.drag.area = 1;
    particleState.mass = 70;
    engine.addPhysicsObject(std::make_unique<Particle>(particleState));

    // particleState.position.x = 100;
    // particleState.position.y = 200;
    // particleState.velocity.y = 50;
    // particleState.velocity.x = 50;
    // particleState.acceleration.x = 10;
    // particleState.acceleration.y = 10;
    // particleState.drag.airDensity = 1.225;
    // particleState.drag.dragCoefficient = 3;
    // particleState.drag.area = 10;
    // particleState.mass = 70;
    // engine.addPhysicsObject(std::make_unique<Particle>(particleState));


    bool running = true;
    SDL_Event event;

    spdlog::trace("Starting a new simulation...");
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }

        spdlog::trace("Updating physics engine...");
        double interpolationFactor = engine.update(); // Update physics and return the interpolationFactor
        
        spdlog::trace("Rendering objects...");
        renderer.renderObjects(engine.getPhysicsObjects(), interpolationFactor); // Now update the render with new positions using interpolationFactor
        renderer.present();   
    }

    spdlog::trace("Simulation finished.");
    return 0;
}
