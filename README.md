# ⚙️ High-Performance C++20 Solitaire Simulation Engine (SFML 3 + SQLite3)

A memory-safe, hardware-accelerated desktop application layout engineered in native C++20 using the SFML 3 graphics and audio framework. This repository serves as a modular application architecture demonstrating clean separation of concerns across visual rendering layers, discrete event streams, type-erased menu state handlers, and persistent telemetry layers.

---

## 🕹️ Application Framework Demonstration

[![Watch the Demo](https://github.com/user-attachments/assets/09a51ea8-bd0a-4083-8aba-72d2de01cadb)](https://youtu.be/o69IuSJAbk4)

*Click the thumbnail image above to watch the full application engine and framework demonstration on YouTube.*

---

## 🚀 Architectural & Technical Highlights

This application serves as a production-grade portfolio project showcasing decoupled design patterns, modern ISO C++ core guidelines, zero-allocation memory constraints, and strict resource safety:

* **Type Erasure & Variant-Visitor Paradigm:** Replaced heavy, pointer-chasing virtual method tables (VTABLEs) and standard inheritance with type-safe heterogeneous rendering blocks using `std::variant` and `std::visit`. By executing button state updates via a structured compile-time overload pattern, the engine packs distinct UI components contiguously in memory—maximizing CPU L1/L2 instruction cache locality while preserving true value semantics.
* **Compile-Time Domain Constraints:** Leverages modern C++20 `<concepts>` and template type traits (`std::is_enum_v`, `std::same_as`) to strictly gate and validate user interface interaction pathways. Custom structural constraints like `Is_Valid_Enum` ensure your button configurations bound cleanly, generating descriptive compiler diagnostic tracks and entirely eliminating runtime exception vectors.
* **Cache-Stable & Non-Owning Memory Views:** Enforces explicit memory boundary management across the simulation layout using non-owning views (`std::span`). Combined with targeted pre-allocations (`std::vector::reserve`) and double-ended queue mappings (`std::deque::assign`), the engine completely eliminates runtime iterator invalidation risks and prevents mid-game heap fragmentation spikes during heavy allocation cycles.
* **Decoupled Data Locality & GPU Shaders:** Visual assets are moved natively into place via zero-copy forwarding constructors (`emplace_back`), eliminating real-time system memory bus contention. The rendering path decouples expensive game-over checks from the frame loop, offloading active location-match indicators directly to the graphics pipeline via a custom hardware-accelerated GLSL fragment shader.
* **Modern Idioms & Clean Interfaces:** Adheres to modern native conventions by completely stripping out raw pointer indirection and manual resource leaks. Features comprehensive use of structural bindings, zero-allocation string parsing (`std::string_view`, `std::from_chars`), dynamic directory loops (`std::filesystem`), and ranges algorithms (`std::ranges::find_if`) to handle execution mechanics safely.
* **Native Transaction Persistence:** Incorporates a robust persistence layer interface embedding the native SQLite3 C-API. Connection streams and core table schemas are wrapped securely inside documentation-ready, smart-managed RAII constructs, ensuring high-integrity serialization of historical game telemetry records without background deadlocks or handle leaks.

---

## 🛠️ Quick Start & Build Guide

### Prerequisites
Ensure your local environment includes a valid installation of Git and CMake.

### Command Line Installation
Execute the following standard build configuration commands inside your native terminal environment to compile the application binaries:

```bash
git clone https://github.com
cd clock_solitaire
cmake -B build
cmake --build build
```

### Linux Dependencies
When building on a Debian-based Linux distribution (such as Ubuntu), install the native SFML supporting dependencies beforehand:
```bash
sudo apt update
sudo apt install \
    libxrandr-dev libxcursor-dev libxi-dev libudev-dev \
    libfreetype-dev libflac-dev libvorbis-dev libgl1-mesa-dev \
    libegl1-mesa-dev libharfbuzz-dev libmbedtls-dev libssh2-1-dev
```

---

## 💻 Workspace Integration

The cross-platform `CMakeLists.txt` build automation schema interfaces natively with all standard contemporary development environments:
* **Visual Studio:** Load via **File > Open > Folder** to trigger auto-generation of the internal CMake cache configuration.
* **VS Code:** Supported directly through integration with the official **CMake Tools Extension**.
* **CLion / Qt Creator:** Handled smoothly through native project directory workspace importing hooks.

---

## ⚙️ Compilation Configurations

### Optimization Toggles
The CMake abstraction flags are mapped via the standard `CMAKE_BUILD_TYPE` flag parameter. For general runtime execution, `Release` mode is recommended to activate full compiler optimizations:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
```
To expose step-through debugger hooks and enable granular binary profiling passes, configure the build directory using the `Debug` parameter variable instead:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

---

## 📜 License
The underlying source code of this application is dual-licensed under Public Domain and the MIT License.
