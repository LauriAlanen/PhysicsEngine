cmake_minimum_required(VERSION 3.12.0)

project(PhysicsEngine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/Include)

set(SRCS
Source/PhysicsEngine.cpp
Source/PhysicsRenderer.cpp
Source/PhysicsSimulation.cpp
Source/PhysicsObjects.cpp
Source/EventManager.cpp
)

set(HDRS
Include/PhysicsEngine.hpp
Include/PhysicsRenderer.hpp
Include/PhysicsSimulation.hpp
Include/PhysicsObjects.hpp
Include/EventManager.hpp
)

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS})

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

target_compile_options(${PROJECT_NAME} PRIVATE -ggdb3 -O0 -Wall)

# Git Submodule Libraries

#SPDLOG
add_subdirectory(third_party/spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

#SDL_ttf
add_subdirectory(third_party/SDL_ttf)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3_ttf::SDL3_ttf)

set(FONT_DIR "${CMAKE_SOURCE_DIR}/Assets/fonts")
add_custom_target(copy_fonts ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${FONT_DIR}"
        "${CMAKE_BINARY_DIR}/fonts"
    COMMENT "Copying fonts to build directory"
)
add_dependencies(${PROJECT_NAME} copy_fonts)

find_package(glm CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)