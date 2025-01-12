#pragma once

#include <PhysicsRenderer.hpp>
#include <PhysicsEngine.hpp>
#include <PhysicsObjects.hpp>
#include <EventManager.hpp>
#include <FPSTracker.hpp>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time() to seed the random number generator
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <chrono>