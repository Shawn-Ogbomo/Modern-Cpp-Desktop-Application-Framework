#include <fstream>
#include <filesystem>
#include "../headers/util.hpp"
#include "../headers/texture_manager.hpp"

auto Texture_manager::load_textures() ->void
{
	std::cout << std::filesystem::current_path();

	for (const auto& dir_entry : std::filesystem::directory_iterator(std::filesystem::path{ "\\clock_solitaire\\" }))
	{
		if (auto dir = dir_entry.path().filename(); dir == "images")
		{
			for (const auto& img_name : std::filesystem::recursive_directory_iterator(dir_entry))
			{
				sf::Texture t;
				t.loadFromFile(img_name);
				textures.emplace_back(t);
			}
		}
	}

	textures.emplace_back(); //empty texture to initialize sprite::card
}