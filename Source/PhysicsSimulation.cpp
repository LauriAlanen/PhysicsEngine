#include <PhysicsSimulation.hpp>

#define SIMULATION_FPS 100.0f

int main() 
{
    spdlog::set_level(spdlog::level::info); // Set global log level to debug
    // auto file_logger = spdlog::basic_logger_mt("file_logger", "logs/debug_log.txt");
    // spdlog::set_default_logger(file_logger);

    spdlog::trace("Initializing Physics Renderer...");
    PhysicsRenderer renderer("Physics Renderer");

	PhysicsEngine engine(SIMULATION_FPS);
    BoundingBox boundingBox(glm::vec2(0, 0), glm::vec2(renderer.w, renderer.h));
    engine.setBoundingBox(boundingBox);

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    renderer.createBoundingBoxTexture(boundingBox);

    bool running = true;

    EventManager eventManager(renderer, engine, boundingBox);
    FPSTracker fpsTracker;

    while (running) 
    {
        eventManager.pollEvents(running);
        fpsTracker.updateFPS();

        double interpolationFactor = engine.update();
        
        renderer.clearScreen();
        renderer.renderTexture();
        renderer.renderObjects(engine.getPhysicsObjects(), interpolationFactor); 
        renderer.renderControls(engine.getPhysicsObjectCount());
        renderer.present();  
    }

    spdlog::trace("Simulation finished.");
    return 0;
}
