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
    virtual ~Texture_Interface() = default;
    virtual auto load_textures() & -> void = 0;
};

struct Card_Manager : public Texture_Interface
{
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
    auto load_textures() & -> void override;
    std::vector<Texture_Forms> textures;
};

struct General_Buttons : public Texture_Interface
{
    General_Buttons() { load_textures(); }

    auto load_textures() & -> void override;

    Texture_Forms textures;
};

struct Text_Boxes : public Texture_Interface
{
    Text_Boxes() { load_textures(); };

    auto load_textures() & -> void override;

    sf::Texture t{ default_texture() };
};

class Texture_Manager
{
public:
    Texture_Manager() = default;
    auto cards() const { return card_manager.textures; }
    auto media_buttons() const{ return button_manager.textures; }
    auto general_buttons() const{ return internal_general_buttons.textures; }
    auto text_boxes() const{ return internal_text_boxes.t; }
private:
    Card_Manager card_manager;
    Button_Manager button_manager;
    General_Buttons internal_general_buttons;
    Text_Boxes internal_text_boxes;
};

#endif // TEXTURE_MANAGER_HPP