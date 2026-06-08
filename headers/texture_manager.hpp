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

inline auto get_texture_manager() -> Texture_manager&
{
	static auto manager = Texture_manager{};
	return manager;
}

#endif //TEXTURE_MANAGER_HPP