set(VCPKG_TARGET_TRIPLET "none" CACHE STRING "" FORCE) 
cmake_minimum_required(VERSION 3.28)
project(clock_solitaire LANGUAGES CXX)

# 1. Global Language Configurations
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Configure default build type (Debug if none is specified)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build." FORCE)
endif()

# Set binary output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 2. Fetch Dependencies
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# 3. Explicit Source List Mapping
set(GAME_SOURCES
    "src/main.cpp"
    "src/board.cpp"
    "src/card.cpp"
    "src/deck.cpp"
    "src/texture_manager.cpp"
    "src/util.cpp"
    "src/time_status.cpp"
    "src/game_status.cpp"
    "src/music_player.cpp"
    "src/button.cpp"
    "src/menu.cpp"
)

# 4. Create the Executable Target
add_executable(main ${GAME_SOURCES})

# 5. Compiler-specific warning flags attached to our target
if(MSVC)
    target_compile_options(main PRIVATE /W4 /permissive-)
    target_compile_options(main PRIVATE /external:W0)
    
    # 6. ONLY set Visual Studio GUI properties if we are generating a Visual Studio Solution!
    if(CMAKE_GENERATOR MATCHES "Visual Studio")
        set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT main)
    endif()
else()
    target_compile_options(main PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# 7. Target Linking
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)
