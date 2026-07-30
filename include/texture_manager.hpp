#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <filesystem>
#include <SFML/Graphics.hpp>

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
	std::vector<sf::Texture> textures;
};

struct Button_Manager : public Texture_Manager_Interface
{
public:
	auto load_textures() -> void override;
	std::vector<std::tuple<sf::Texture, sf::Texture, sf::Texture>> textures;
};

//class Card_Manager: public Texture_Manager
//{
//public:
//	virtual auto load_textures() -> void;
//	std::vector<std::pair<std::string, sf::Texture>> textures;
//private:
//};

#endif // TEXTURE_MANAGER_HPP