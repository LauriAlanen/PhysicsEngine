# Physics Simulator

A modular and efficient 2D physics simulation engine supporting Euler and Verlet integration methods. The simulator features complete separation of physics and rendering processes, ensuring smooth and accurate simulations independent of rendering performance.

---

## Basic Example Simulation
https://github.com/user-attachments/assets/7d87bf04-55f6-468e-bcc6-c737f336139c


## Features

### Physics Engine
- **Integration Methods**: Supports both **Euler** and **Verlet** integration.
- **Interpolation**: Implements physics interpolation using an interpolation factor, allowing smooth rendering of objects between physics updates.
- **Collision Detection**: Includes collision detection with a bounding box.
- **Basic Forces**:
  - **Gravity**
  - **Air Resistance**
- **High Modularity**: Key functions are encapsulated in separate classes. Modular parts are implemented as virtual classes to enable easy customization and extensibility.
- **Spatial Hash Grid** (**WIP**): Efficient collision handling between particles is under development.

### Rendering
- **FPS Independence**: Rendering frame rate does not affect the physics frame rate.
- **Bounding Box Visualization**: Includes a grid rendering for visualizing the bounding box.
---

## Getting Started

### Prerequisites
- SDL3 for rendering [https://github.com/libsdl-org/SDL/releases]
- SDL3 TTF. Install from [https://github.com/libsdl-org/SDL_ttf]
- `glm` for vector math. Install using `sudo apt install -y libglm-dev`
- `spdlog` for logging. Install using `sudo apt install -y libspdlog-dev`

## Roadmap
- [x] Implement Euler and Verlet integration.
- [x] Add bounding box collision detection.
- [x] Separate physics and rendering processes.
- [ ] Implement spatial hash grid for particle-particle collision.
- [ ] Extend force system for custom forces.
- [ ] Add support for more complex shapes and constraints.

