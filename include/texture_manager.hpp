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

struct Button_Manager : public Texture_Manager_Interface 
{
public:
    auto load_textures() & -> void override;
    std::vector<std::tuple<sf::Texture, sf::Texture, sf::Texture>> textures;
};

/// TODO: Provide a way for each type using this to share the same instance
/// TODO: This will eliminate declaring an instance of general_Buttons_Interface in every type that is using the textures 
/// TODO: Use a reference or a std::shared_ptr
struct General_Buttons : public Texture_Manager_Interface
{
public:
    auto load_textures() & -> void override;
   
    auto get_textures() & -> const General_Buttons&
    {
        static const auto texture_manager = General_Buttons{};
        return texture_manager;
    }

    std::tuple<sf::Texture, sf::Texture, sf::Texture> textures{default_texture()
        ,default_texture(),default_texture() };
};

#endif // TEXTURE_MANAGER_HPP