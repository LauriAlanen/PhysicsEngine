#include <EventManager.hpp>

void EventManager::pollEvents(bool& running)
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) 
    {
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
}