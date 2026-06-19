cmake_minimum_required(VERSION 3.28)
project(clock_solitaire LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(main "src/main.cpp" "src/board.cpp" "src/card.cpp" "src/deck.cpp" "src/game.cpp" "src/texture_manager.cpp" "src/util.cpp" "src/time_status.cpp" "src/game_status.cpp" "src/music_player.cpp")
if(MSVC)
    # Sets warning level 4 (/W4) for the Visual Studio compiler
    target_compile_options(main PRIVATE /W4)
    
    # Optional: Suppress external SFML header noise so you only see your own warnings
    target_compile_options(main PRIVATE /external:W0)
endif()
target_compile_features(main PRIVATE cxx_std_17)
target_link_libraries(main PRIVATE SFML::Graphics SFML::Audio)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
