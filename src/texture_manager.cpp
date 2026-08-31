#include <filesystem>
#include <utility>

#include "../include/directory_manager.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

namespace fs = std::filesystem;

auto Card_Manager::load_textures() & -> void
{
    textures.reserve((Board::total_piles * Board::cards_pile) + 1);

    for (const auto& dir_entry : fs::directory_iterator{ Directory_Manager::assets_dir() / "images" })
    {
        auto& card_name = dir_entry.path();
        textures.emplace_back(std::pair{ card_name.filename().stem(), sf::Texture{ card_name } });
    }
}

auto Button_Manager::load_textures() & -> void
{
    const auto buttons = sf::Image{ Directory_Manager::assets_dir() / "buttons" / "buttons_clock_solitare.png" };
    const auto dimmensions_button = sf::Vector2i{ 30, 30 };
    const auto dimmensions_image = sf::Vector2i{ static_cast<sf::Vector2i>(buttons.getSize()) - dimmensions_button };

    const auto& t = [&](int x, int y = 0) -> std::tuple<sf::Texture, sf::Texture, sf::Texture> {
        return std::make_tuple(sf::Texture{ buttons, false, { { x, y }, dimmensions_button } },
            sf::Texture{ buttons, false, { { x, (y + dimmensions_button.y) }, dimmensions_button } },
            sf::Texture{ buttons, false, { { x, (y + (dimmensions_button.y * 2)) }, dimmensions_button } });
        };

    textures.reserve(buttons.getSize().x / dimmensions_button.x);

    for (auto i = 0; i <= dimmensions_image.x; i += dimmensions_button.x)
    {
        textures.emplace_back(t(i));
    }
}

auto General_Buttons::load_textures() & -> void
{
     textures = std::make_tuple(
        sf::Texture{ Directory_Manager::assets_dir() / "buttons" / "general_button_state_1.png" },
        sf::Texture{ Directory_Manager::assets_dir() / "buttons" / "general_button_state_2.png" },
        sf::Texture{ Directory_Manager::assets_dir() / "buttons" / "general_button_state_3.png" });
}