// Not used yet....

#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <PhysicsEngine.hpp>
#include <PhysicsObjects.hpp>

TEST_CASE("Test Frame Time Clamping") {
    Bounds simulationBounds(0, 0, 0, 0);
	PhysicsEngine engine(60, simulationBounds);
    engine->previousTime = SDL_GetPerformanceCounter();
    SDL_Delay(1000);  // Simulate a large frame time

    double interpolationFactor = engine.update();

    REQUIRE(engine.frameTime == 0.25f);  // Ensure frameTime is clamped to 0.25f
    REQUIRE(engine.accumulator == 0.25f);  // Ensure accumulator is set to 0.25f
}

TEST_CASE("Test Accumulator Logic") {
    PhysicsEngine engine;
    engine.deltaTime = 0.016f;  // 60 FPS step
    engine.accumulator = 0.05f; // Pre-fill accumulator

    engine.update();  // Perform the update

    REQUIRE(engine.accumulator == 0.034f);  // Accumulator should reduce by deltaTime
    REQUIRE(engine.simulationTime == 0.016f);  // Should step forward once
}