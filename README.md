# 🃏 Clock Solitaire (SFML 3 + C++20)

A performance-focused desktop simulation of the classic **Clock Solitaire** card game built using modern C++20 and the SFML graphics/audio library framework.

---

## 🕹️ Application Demonstration

[![Watch the Demo](https://github.com/user-attachments/assets/303c70a1-bcc7-427b-9bab-adde5440f3a7)](https://youtu.be/wYRtLFo7jkg)

*Click the thumbnail image above to watch the full application demonstration on YouTube.*

---

## 🚀 Architectural & Technical Highlights

This application serves as a portfolio project showcasing modern C++ design patterns, deterministic resource tracking, and frame-loop state optimization:

* **Static Dispatch & Compile-Time Constraints:** Leverages C++20 `<concepts>` to validate template type traits across real-time user interface events. Features a custom constraint (`Is_Valid\_Enum`) to bound state-button configurations, providing clean compiler diagnostics and eliminating runtime exception pathways.
* **Hybrid Stable Memory Architecture:** Implements a calculated container arrangement pairing a contiguous asset registry with individual pile layout structures. By utilizing `std::vector::reserve` alongside `std::deque` allocations for cards, the engine achieves true O(1) front/back insertions without element-shifting penalties or iterator invalidation.
* **Data Locality & Resource Decoupling:** Prioritizes object locality by storing card elements sequentially in block allocations to maximize CPU L1/L2 cache-line retention. Telemetry evaluations are decoupled from the tight frame rendering pass by sharing a clock resource via smart pointers, restricting state checks strictly to active menu boundaries to reduce background CPU cycles.
* **Modern Idioms & Clean Interfaces:** Eliminates raw pointer indirection by leveraging standard library customization points, structured bindings, directory iterators (`std::filesystem`), and ranges algorithms (`std::ranges::find_if`) to process layout maps safely.

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
