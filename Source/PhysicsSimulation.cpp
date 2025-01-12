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

    auto lastTime = std::chrono::high_resolution_clock::now(); 
    int frameCount = 0;
    float fps = 0.0f;

    EventManager eventManager(renderer, engine, boundingBox);

    while (running) 
    {
        eventManager.pollEvents(running);

        double interpolationFactor = engine.update();
        
        renderer.clearScreen();
        renderer.renderTexture();
        renderer.renderObjects(engine.getPhysicsObjects(), interpolationFactor); 
        renderer.renderControls(engine.getPhysicsObjectCount());
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
