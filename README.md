# 🃏 Clock Solitaire (SFML + C++17/C++20)

A highly optimized desktop implementation of the classic **Clock Solitaire** card game built using modern C++20 and the SFML graphics/audio library. 

---

## 🕹️ Application Demonstration

[![Watch the Demo](https://github.com/user-attachments/assets/3a796f64-3711-4d38-91d2-2f0e360bd56e)](https://youtu.be/PGnCHys6Qxk)

*Click the thumbnail image above to watch the full application demonstration on YouTube.*

---

## 🚀 Key Technical Highlights

This application serves as a high-performance portfolio project showcasing precise data structure management and hardware-level loop optimizations:
- **Modern C++20 Standard:** Leverages modern paradigms including structured bindings inside range-based loops, standard library customization points, and explicit constraint awareness.
- **Stable Memory Architecture:** Utilizes a highly disciplined container strategy using **`std::vector` and `std::deque`**. By combining localized `reserve()` configurations with `std::deque`'s non-relocating memory nature, all iterators and object references remain perfectly stable across the entire runtime without the overhead of heap-allocated smart pointers.
- **Cache-Friendly Loop Performance:** Prioritizes values over heap allocations, keeping card data contiguous in memory. Bypasses branch prediction penalties entirely by allowing primitive-type pointer and iterator comparisons to resolve directly in the hardware pipeline.
- **Upcoming Integrations:** Core system logic is extensively decoupled and refactored to support seamless sequential expansion into localized **SQLite storage** for player analytics alongside async **multi-threading capabilities**.


---

## 🛠️ Quick Start & Build Guide

### Prerequisites
Ensure you have [Git](https://git-scm.com/downloads) and [CMake](https://cmake.org/download/) installed on your machine.

### Command Line Installation
Clone this repository and compile the build targets using the following standard commands in your root terminal workspace:

```bash
git clone https://github.com
cd Clock-Solitaire
cmake -B build
cmake --build build
```

### Linux Dependencies
If you are building the application on a Debian-based Linux environment (like Ubuntu), install the native SFML support libraries beforehand:
```bash
sudo apt update
sudo apt install \
    libxrandr-dev libxcursor-dev libxi-dev libudev-dev \
    libfreetype-dev libflac-dev libvorbis-dev libgl1-mesa-dev \
    libegl1-mesa-dev libharfbuzz-dev libmbedtls-dev libssh2-1-dev
```

---

## 💻 IDE Workspaces

This project features native cross-platform configuration file structures (`CMakeLists.txt`) compatible with all major modern text editors:
* **Visual Studio:** Choose **File > Open > Folder** to load the root workspace directory. Visual Studio will natively generate the local CMake cache configurations automatically.
* **VS Code:** Supported directly via the official **CMake Tools Extension**.
* **CLion / Qt Creator:** Handled seamlessly through native project layout importing hooks.

---

## ⚙️ Build Options

### Changing Compiler Optimizations
CMake abstracts compiler flags via the `CMAKE_BUILD_TYPE` parameter. By default, `Release` mode is recommended to activate maximum code optimizations:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
```
For deep profiling and step-through debugging targets, pass the `Debug` variable hook instead:
```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug
```

---

## 📜 License
The underlying source code of this application is dual-licensed under Public Domain and the MIT License. Feel free to use, modify, or reference it as you see fit.
