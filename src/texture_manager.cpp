#include <fstream>
#include <filesystem>
#include "../headers/util.hpp"
#include "../headers/texture_manager.hpp"

auto Texture_manager::load_textures() ->void
{
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

		//if music
			//load all of the songs into the vector of songs

		//if fonts
			//load all fonts...

		// if sounds
			//load all sounds
	}

	textures.emplace_back(); //empty texture to initialize sprite::card
}