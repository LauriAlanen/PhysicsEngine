#include <PhysicsSimulation.hpp>

#define SIMULATION_FPS 100.0f

int main() 
{
    spdlog::set_level(spdlog::level::info); // Set global log level
    PhysicsRenderer renderer("Physics Renderer");
    

    SDLPrimitives primitives(renderer);

	PhysicsEngine engine(SIMULATION_FPS);
    BoundingBox boundingBox(glm::vec2(0, 0), glm::vec2(renderer.w, renderer.h));
    engine.setBoundingBox(boundingBox);

    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator

    renderer.createBoundingBoxTexture(boundingBox); // Draw a grid because renderer is given as parameter
    SpatialHash spatialHash(renderer, boundingBox);

    bool running = true;

    EventManager eventManager(renderer, engine, boundingBox);
    FPSTracker fpsTracker;
    Controls controls;
    while (running) 
    {
        eventManager.pollEvents(running);
        fpsTracker.updateFPS();

        double interpolationFactor = engine.update();

        renderer.clearScreen();
        renderer.renderTexture();
        renderer.renderObjects(engine.getPhysicsObjects(), interpolationFactor); 

        controls.particleCount = engine.getPhysicsObjectCount();
        controls.physicsFps = SIMULATION_FPS;
        controls.renderfps = fpsTracker.getFPS();
        renderer.renderControls(controls);
        
        renderer.present();  
    }

    spdlog::trace("Simulation finished.");
    return 0;
}
