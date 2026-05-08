#include <fstream>
#include <filesystem>
#include "../headers/util.hpp"
#include "../headers/texture_manager.hpp"

auto Texture_manager::load_textures() ->void
{
	std::filesystem::path image_names{ "../../../../txt/card_names.txt" };	//revise this to remove all of the ../

	std::ifstream ifs{ image_names.string() };

	Util::check_stream(ifs, "unable to open stream...\n");

	std::filesystem::path images_dir{ "../../../../images/" }; //revise this to remove all of the ../

	sf::Texture back_texture;

	if (!back_texture.loadFromFile(images_dir.string() + "card-back2.png"))
	{
		throw std::invalid_argument{ "image does not exist...\n" };
	}

	textures.emplace_back(back_texture);

	for (std::string s; ifs >> s;)
	{
		sf::Texture t;

		if (!t.loadFromFile(images_dir.string() + s))
		{
			throw std::invalid_argument{ "couldn't load file: " + s + "\n" };
		}

		textures.emplace_back(t);
	}
	
	textures.emplace_back(sf::Texture{}); //empty texture to initialize sprite::card
}