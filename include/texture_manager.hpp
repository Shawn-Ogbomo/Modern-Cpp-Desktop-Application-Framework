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

struct Texture_Interface
{
public:
    virtual ~Texture_Interface() = default;
    virtual auto load_textures() & -> void = 0;
};

struct Card_Manager : public Texture_Interface
{
public:
    auto load_textures() & -> void override;
    std::vector<std::pair<std::filesystem::path, sf::Texture>> textures;
};

struct Texture_Forms
{
    sf::Texture f1{ default_texture() };
    sf::Texture f2{ default_texture() };
    sf::Texture f3{ default_texture() };
};

struct Button_Manager : public Texture_Interface
{
public:
    auto load_textures() & -> void override;
    std::vector<Texture_Forms> textures;
};

struct General_Buttons : public Texture_Interface
{
public:
    General_Buttons() { load_textures(); }

    auto load_textures() & -> void override;

    Texture_Forms textures;
};

struct Text_Boxes : public Texture_Interface
{
public:
    Text_Boxes() { load_textures(); };

    auto load_textures() & -> void override;

    sf::Texture t{ default_texture() };
};

class Texture_Manager
{
public:
    Texture_Manager() = default;
    auto cards();
    auto media_buttons();
    auto general_buttons();
    auto text_boxes();
private:
    Card_Manager internal_card_manager;
    Button_Manager internal_button_manager;
    General_Buttons internal_general_buttons;
    Text_Boxes internal_text_boxes;
};

#endif // TEXTURE_MANAGER_HPP