#include <filesystem>
#include <utility>

#include "../include/directory_manager.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

namespace fs = std::filesystem;

auto Card_Manager::load_textures() & -> void
{
    for (auto index = 0; const auto& dir_entry 
        : fs::directory_iterator{ Directory_Manager::assets_dir() / "images" })
    { 
        auto& card_name = dir_entry.path();
        internal_textures[index] 
            = (std::pair{ card_name.filename().stem(), sf::Texture{ card_name } });
        
        ++index;
    }
}

auto Button_Manager::load_textures() & -> void
{
    const auto buttons = sf::Image{ Directory_Manager::assets_dir() / "buttons" / "buttons_clock_solitare.png" };
    const auto dimmensions_button = sf::Vector2i{ 30, 30 };
    const auto dimmensions_image = sf::Vector2i{ static_cast<sf::Vector2i>(buttons.getSize()) - dimmensions_button };

    const auto& t = [&, this](int x, int y = 0) -> Texture_Forms
        {
            return Texture_Forms{ sf::Texture{ buttons, false, { { x, y }, dimmensions_button } },
                sf::Texture{ buttons, false, { { x, (y + dimmensions_button.y) }, dimmensions_button } },
                sf::Texture{ buttons, false, { { x, (y + (dimmensions_button.y * 2)) }, dimmensions_button } } };
        };

    for (auto index = 0; auto& texture : internal_textures)
    {
        texture = (t(index));
        index += dimmensions_button.x;
    }
}

auto General_Buttons::load_textures() & -> void
{
    internal_textures.f1 = sf::Texture{ Directory_Manager::assets_dir() / "buttons" / "general_button_state_1.png" };
    internal_textures.f2 = sf::Texture{ Directory_Manager::assets_dir() / "buttons" / "general_button_state_2.png" };
    internal_textures.f3 = sf::Texture{ Directory_Manager::assets_dir() / "buttons" / "general_button_state_3.png" };
}

auto Text_Boxes::load_textures() & ->void
{
    t = sf::Texture{ Directory_Manager::assets_dir() / "text_box"
    / "confirmation_menu.png", false, { {05,435}, {315,165 } } };
}