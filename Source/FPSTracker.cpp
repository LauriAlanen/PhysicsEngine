#include <FPSTracker.hpp>

FPSTracker::FPSTracker() 
    : frameCount(0), fps(0.0f), lastTime(std::chrono::high_resolution_clock::now()) {}

void FPSTracker::updateFPS() {
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
