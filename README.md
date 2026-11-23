# Mini Metro

A **Mini Metro**–inspired 3D transit and railway management game written in **C++** and **OpenGL** using the [UPB-Graphics `gfx-framework`](https://github.com/UPB-Graphics/gfx-framework), developed for the *Elements of Computer Graphics (EGC)* course at the Polytechnic University of Bucharest.

<img width="800" height="453" alt="output" src="https://github.com/user-attachments/assets/ba6f6b5a-cdf4-4977-8b8a-7c2132b8089e" />

---

## Overview

Build and manage a railway network connecting stations across a 3D map. Dispatch trains with carriages along custom-built railroads, keep passenger flow moving, and prevent stations from overcrowding.

### Core Modules
- **Stations (`station.h/.cpp`):** Station entities with distinct types/visuals, passenger generation, and capacity handling.
- **Trains & Carriages (`train.h/.cpp`, `carriage.h/.cpp`):** Locomotive and carriage logic for traversing tracks, carrying passengers, and following connected rail paths.
- **Rails & Railroads (`rail.h/.cpp`, `railroad.h/.cpp`):** Individual rail segments and full railroad networks managing track geometry, connections, and routing.
- **Scene & Rendering (`tema2.h/.cpp`, `shaders/`):** Main game loop, camera handling, input processing, and custom OpenGL vertex/fragment shaders (`VertexShader.glsl`, `FragmentShader.glsl`).

---

## Controls

| Input | Action |
| :--- | :--- |
| **W / A / S / D** | Move camera |
| **Right-Click + Drag** | Rotate / orbit camera |
| **Scroll Wheel** | Zoom in / out |
| **Left-Click** | Select / interact with stations & rails |
| **Space** | Pause / resume simulation |
| **R** | Restart game |

*(Update the table above if your `tema2.cpp` uses different keybindings.)*

---

## Project Structure

```text
├── deps/                       # Prebuilt & header dependencies (GLFW, GLEW, Assimp, FreeType, spdlog)
├── infra/                      # CMake utility scripts
├── src/
│   ├── main.cpp                # Entry point
│   ├── core/                   # Framework engine, windowing, and GPU wrappers
│   ├── components/             # Camera, transform, SimpleScene, and text renderer
│   └── lab_m1/
│       └── tema2/
│           ├── tema2.h / .cpp        # Main scene, game loop, and rendering
│           ├── station.h / .cpp      # Station logic and rendering
│           ├── train.h / .cpp        # Train movement and state
│           ├── carriage.h / .cpp     # Train carriage logic
│           ├── rail.h / .cpp         # Rail segment geometry and state
│           ├── railroad.h / .cpp     # Railroad network management
│           └── shaders/
│               ├── VertexShader.glsl
│               └── FragmentShader.glsl
└── CMakeLists.txt
