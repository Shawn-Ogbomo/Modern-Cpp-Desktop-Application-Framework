#include <fstream>
#include <filesystem>
#include "../headers/util.hpp"
#include "../headers/texture_manager.hpp"

auto Texture_manager::load_textures() ->void
{
	for (const auto& img_name : std::filesystem::recursive_directory_iterator({ "\\clock_solitaire\\images" }))
	{
		sf::Texture t;

		if (!t.loadFromFile(img_name))
		{
			throw Invalid_file{ "The file: " + img_name.path().string() + " does not exist...\n" };
		}

		textures.emplace_back(t);
	}

	textures.emplace_back(); //empty texture to initialize sprite::card
}