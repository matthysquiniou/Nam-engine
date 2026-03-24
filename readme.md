# NAM Engine

A custom C++ game engine built with **DirectX 12**, featuring an **Entity‑Component‑System (ECS)** architecture, a flexible rendering pipeline, integrated physics and collision detection, particle effects, UI components, and procedural generation utilities.

---

## Installation and Solution Generation

1. Go to the `bin/` folder.  
2. Run `make.bat`.  
3. The script will generate an `ide/` folder containing `nam_engine.sln`.  
4. Open the Visual Studio solution.  

---

## Features

### Entity‑Component‑System (ECS)
- **Type‑safe component storage** using sparse sets with paging for cache efficiency.
- **Fast component queries** via templated views that refresh automatically when entities are added/removed.
- **Systems** (e.g., rendering, physics, UI) can be enabled/disabled individually.
- **GameObject** wrapper that simplifies the ECS for gameplay code.

### Rendering (DirectX 12)
- **3D rendering** with support for diffuse textures and multiple light types (directional, point, spot).
- **2D rendering** for sprites and text with alpha blending and custom draw order.
- **GPU‑driven particle system** using compute shaders (update, spawn, draw).
- **Albedo‑only material** (no full material system – only basic diffuse shading).

### Physics & Collision
- **Axis‑aligned bounding box** and **oriented bounding box** support.
- **Sphere colliders** and **box colliders** with optional mesh‑based or custom extents.
- **Spatial hash** for efficient broad‑phase collision detection.
- **Impulse‑based collision response** with mass and restitution.
- **Gravity** and **velocity integration** for rigid bodies.

### UI System
- **Button components** with hover, click, and leave events.
- **UISystem** that handles mouse interaction with rotated sprites.
- **Text rendering** with custom kerning, character sets, and draw layers.

### Procedural Generation
- **Perlin noise** for terrain/heightmap generation.
- **Poisson disc sampling** for evenly distributed random points.
- **Voxel grid** utilities (sphere, box, hole carving) and mesh extraction.

---

## Dependencies

- **Windows SDK** (for DirectX 12)
- **DirectX 12** (D3D12, DXGI, D3DCompiler)
- **C++17** (or later) compiler (tested with MSVC)