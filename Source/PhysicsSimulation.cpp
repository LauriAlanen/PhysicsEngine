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
    
    // for (int i = 0; i < 1000; ++i) {
    //     BasicState particle;

    //     // Randomize position (within SDL_FRect)
    //     particle.position.x = boundingBox.position.x + (rand() % static_cast<int>((boundingBox.position.x + boundingBox.size.x - boundingBox.position.x * 2 + 1)));
    //     particle.position.y = boundingBox.position.y + (rand() % static_cast<int>((boundingBox.position.y + boundingBox.size.y - boundingBox.position.y * 2 + 1)));

    //     // Randomize velocity (e.g., velocity between -10 and 10 for both x and y components)
    //     particle.velocity.x = (rand() % 21 - 10); // Random velocity between -10 and 10
    //     particle.velocity.y = (rand() % 21 - 10); // Random velocity between -10 and 10

    //     // Randomize acceleration (e.g., acceleration between -5 and 5 for both x and y components)
    //     particle.acceleration.x = (rand() % 11 - 5); // Random acceleration between -5 and 5
    //     particle.acceleration.y = (rand() % 11 - 5); // Random acceleration between -5 and 5

    //     // Drag properties (constant or slightly varied)
    //     particle.drag.airDensity = 1.225; // Standard air density
    //     particle.drag.dragCoefficient = 0.47; // Drag coefficient for a sphere
    //     particle.drag.area = 1 + (rand() % 10) / 10.0f; // Random area between 1.0 and 2.0

    //     // Randomize mass
    //     particle.mass = 50 + rand() % 101; // Random mass between 50 and 150

    //     // Add the particle to the physics engine
    //     engine.addPhysicsObject(std::make_unique<Particle>(particle));
    // }

    renderer.createBoundingBoxTexture(boundingBox);

    bool running = true;
    SDL_Event event;

    auto lastTime = std::chrono::high_resolution_clock::now(); 
    int frameCount = 0;
    float fps = 0.0f;
    bool mousePressed = false;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) 
            {
                running = false;
            }

            if (event.type == SDL_EVENT_MOUSE_WHEEL)
            {
                renderer.handleZoom(event);
            }

            if (event.type == SDL_EVENT_WINDOW_PIXEL_SIZE_CHANGED)
            {
                glm::vec2 newSize = {event.window.data1, event.window.data2};
                engine.modifyBoundingBox(boundingBox.position, newSize);
                spdlog::info("Updating BoundingBox new size is {} {}.", event.window.data1, event.window.data2);
            }
            
            if (event.type == SDL_EVENT_MOUSE_BUTTON_DOWN) 
            {
                if (event.button.button == SDL_BUTTON_LEFT) 
                {
                    mousePressed = true;
                }
            }

            if (event.type == SDL_EVENT_MOUSE_BUTTON_UP) 
            {
                if (event.button.button == SDL_BUTTON_LEFT) 
                { 
                    mousePressed = false;
                }
            }

            if (event.type == SDL_EVENT_MOUSE_MOTION) 
            {
                if (mousePressed) 
                {
                    BasicState particle = engine.generateRandomParticle(glm::vec2(event.motion.x, renderer.h - event.motion.y));
                    engine.addPhysicsObject(std::make_unique<Particle>(particle));
                }
            }
        }
        spdlog::trace("Updating physics engine...");
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
