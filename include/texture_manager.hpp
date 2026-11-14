#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SFML/Graphics.hpp>

#include <filesystem>
#include <ranges>

inline auto default_texture() -> const sf::Texture&
{
    static const auto  t = sf::Texture{};
    return t;
}

struct Card_Manager
{
    auto load_textures() & -> void;
    std::vector<std::pair<std::filesystem::path, sf::Texture>> textures;
};

struct Texture_Forms
{
    sf::Texture f1{ default_texture() };
    sf::Texture f2{ default_texture() };
    sf::Texture f3{ default_texture() };
};

struct Button_Manager
{
    Button_Manager() { load_textures(); }
    auto load_textures() & -> void;
    std::vector<Texture_Forms> textures;
};

struct General_Buttons
{
    General_Buttons() { load_textures(); }
    auto load_textures() & -> void;
    Texture_Forms textures;
};

struct Text_Boxes
{
    Text_Boxes() { load_textures(); };
    auto load_textures() & -> void;
    sf::Texture t{ default_texture() };
};

class Texture_Manager
{
public:
    Texture_Manager() = default;
    auto cards() const& -> const Card_Manager&{ return card_manager; }
    auto media_buttons() const& -> const Button_Manager&{ return button_manager; }
    auto general_buttons() const& ->const General_Buttons&{ return internal_general_buttons; }
    auto text_boxes() const& -> const Text_Boxes&{ return internal_text_boxes; }
private:
    Card_Manager card_manager;
    Button_Manager button_manager;
    General_Buttons internal_general_buttons;
    Text_Boxes internal_text_boxes;
};

#endif // TEXTURE_MANAGER_HPP