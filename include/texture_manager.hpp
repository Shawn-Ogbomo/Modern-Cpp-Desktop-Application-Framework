#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <filesystem>
#include <SFML/Graphics.hpp>

class Texture_Manager_test
{
public:
	virtual auto load_textures() -> void = 0;
private:
};

struct Texture_manager
{
public:
	auto load_textures() -> void;
	std::vector<sf::Texture> textures;
};

inline auto get_texture_manager() -> Texture_manager&
{
	static auto manager = Texture_manager{};
	return manager;
}

//class Card_Manager: public Texture_Manager
//{
//public:
//	virtual auto load_textures() -> void;
//	std::vector<std::pair<std::string, sf::Texture>> textures;
//private:
//};

struct Button_Manager: public Texture_Manager_test
{
public:
	 virtual auto load_textures() -> void;
	std::vector<std::tuple<sf::Texture, sf::Texture, sf::Texture>> textures;
};

//template this...
inline auto get_texture_manager_test() -> Button_Manager&
{
	static auto manager = Button_Manager{};
	return manager;
}

#endif // TEXTURE_MANAGER_HPP