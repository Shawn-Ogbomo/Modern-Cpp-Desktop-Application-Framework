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

class Card_Manager
{
    static constexpr auto limit = 53;
    using Pair_Path_Texture = std::pair<std::filesystem::path, sf::Texture>;
    using Card_Textures = std::array<Pair_Path_Texture, limit>;
public:
    Card_Manager() { load_textures(); }
    auto textures()const& -> const Card_Textures& { return internal_textures; }
private:
    auto load_textures() & -> void;
    Card_Textures internal_textures;
};

struct Texture_Forms
{
    sf::Texture f1{ default_texture() };
    sf::Texture f2{ default_texture() };
    sf::Texture f3{ default_texture() };
};

class Button_Manager
{
    static constexpr auto limit = 5;
    using Media_Textures = std::array<Texture_Forms, limit>;
public:
    Button_Manager() { load_textures(); }

    auto textures()const&
        -> const Media_Textures&
    {
        return internal_textures;
    }
private:
    auto load_textures() & -> void;
    Media_Textures internal_textures;
};

class General_Buttons
{
public:
    General_Buttons() { load_textures(); }

    auto textures() const&
        -> const Texture_Forms&
    {
        return internal_textures;
    }
private:
    auto load_textures() & -> void;
    Texture_Forms internal_textures;
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
    auto cards() const& -> const Card_Manager& { return card_manager; }
    auto media_buttons() const& -> const Button_Manager& { return button_manager; }
    auto general_buttons() const& ->const General_Buttons& { return internal_general_buttons; }
    auto text_boxes() & ->  sf::Sprite& { return text_box; }
private:
    Card_Manager card_manager;
    Button_Manager button_manager;
    General_Buttons internal_general_buttons;
    Text_Boxes internal_text_boxes;
    sf::Sprite text_box{ internal_text_boxes.t };
};

#endif // TEXTURE_MANAGER_HPP