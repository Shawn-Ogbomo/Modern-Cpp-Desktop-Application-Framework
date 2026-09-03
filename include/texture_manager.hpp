#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <filesystem>

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

struct General_Buttons : public Texture_Manager_Interface
{
    sf::Texture t{};
public:
    auto load_textures() & -> void override;
   
    auto get_textures() & -> const General_Buttons&
    {
        static auto texture_manager = General_Buttons{};
        return texture_manager;
    }

    std::tuple<sf::Texture, sf::Texture, sf::Texture> textures{t,t,t};
};

#endif // TEXTURE_MANAGER_HPP