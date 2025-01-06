# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(PhysicsEngine VERSION 1.0 LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the include directory for header files
include_directories(${CMAKE_SOURCE_DIR}/Include)
# Add source files
set(SRCS
Source/PhysicsEngine.cpp
Source/PhysicsRenderer.cpp
Source/PhysicsSimulation.cpp
Source/PhysicsObjects.cpp
Source/SimulationObjects.cpp
)

# Add header files (optional but good practice for IDE support)
set(HDRS
Include/PhysicsEngine.hpp
Include/PhysicsRenderer.hpp
Include/PhysicsSimulation.hpp
Include/PhysicsObjects.hpp
Include/SimulationObjects.hpp
)

# Add the executable
add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

# Find SDL2 and SDL2_image
find_package(SDL2 REQUIRED)

# Include SDL2 and SDL2_image include directories
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

# Link SDL2 and SDL2_image libraries
target_link_libraries(${PROJECT_NAME} PRIVATE ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} m)

# Add debug flags
target_compile_options(${PROJECT_NAME} PRIVATE -ggdb3 -O0 -Wall)

# --- Testing Setup ---
# Add Catch2 as a subdirectory (Assumes Catch2 is in third_party)
# add_subdirectory(third_party/Catch2)

# # Add test source files
# set(TEST_SRCS
#     Tests/TestPhysicsEngine.cpp  # Your test source file(s)
# )

# # Create the test executable
# add_executable(runTests ${TEST_SRCS})

# # Link Catch2 to the test executable
# target_link_libraries(runTests Catch2::Catch2)

# # Enable testing
# enable_testing()

# # Add the test to CTest
# add_test(NAME PhysicsEngineTest COMMAND runTests)

add_subdirectory(third_party/spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)