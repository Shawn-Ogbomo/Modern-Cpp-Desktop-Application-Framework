#ifndef TEXTURE_MANAGER_HPP
#define TEXTURE_MANAGER_HPP

#include <filesystem>
#include <SFML/Graphics.hpp>

struct Texture_manager
{
public:
	auto load_textures() -> void;
	std::vector<sf::Texture> textures;
};

inline Texture_manager& get_texture_manager()
{
	static Texture_manager manager;
	return manager;
}

#endif //TEXTURE_MANAGER_HPP