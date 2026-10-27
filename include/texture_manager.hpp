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

struct Texture_Manager_Interface
{
public:
    virtual ~Texture_Manager_Interface() = default;
    virtual auto load_textures() & -> void = 0;
};

struct Card_Manager : public Texture_Manager_Interface
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

struct Button_Manager : public Texture_Manager_Interface
{
public:
    auto load_textures() & -> void override;
    std::vector<Texture_Forms> textures;
};

struct General_Buttons : public Texture_Manager_Interface
{
public:
    General_Buttons() { load_textures(); }

    auto load_textures() & -> void override;

    Texture_Forms textures;
};

struct Text_Boxes : public Texture_Manager_Interface
{
public:
    Text_Boxes() { load_textures(); };

    auto load_textures() & -> void override;

    sf::Texture t{ default_texture() };
};
#endif // TEXTURE_MANAGER_HPP