#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <filesystem>

struct Texture_Manager_Interface 
{
public:
    virtual ~Texture_Manager_Interface() = default;
    virtual auto load_textures() -> void = 0;
};

struct Card_Manager : public Texture_Manager_Interface 
{
public:
    auto load_textures() -> void override;
    std::vector<std::pair<std::filesystem::path, sf::Texture>> textures;
};

struct Button_Manager : public Texture_Manager_Interface 
{
public:
    auto load_textures() -> void override;
    std::vector<std::tuple<sf::Texture, sf::Texture, sf::Texture>> textures;
};

///Test
////////////////////////////////////////////////////////////////////////////////////////////////////////
// prev, pause, play , next, stop 
struct Media : public Button_Manager
{
public: 
    auto load_textures() -> void override;
    std::vector<std::tuple<sf::Texture, sf::Texture, sf::Texture>> textures;
};

//pause, resume, restart 
struct State : public Button_Manager //rename the derived class
{
public:
    auto load_textures() -> void override;
    std::vector<std::tuple<sf::Texture, sf::Texture, sf::Texture>> textures;
};

// yes, no, ok, quit , hint 
struct General : public Button_Manager
{
public:
    auto load_textures() -> void override;
    std::vector<std::tuple<sf::Texture, sf::Texture, sf::Texture>> textures;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TEXTURE_MANAGER_HPP