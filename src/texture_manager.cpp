#include <utility>
#include <fstream>
#include <filesystem>

#include "../headers/util.hpp"
#include "../headers/texture_manager.hpp"

auto Texture_manager::load_textures() ->void
{
	auto card_names = std::filesystem::path{ "..\\..\\..\\..\\txt\\card_names.txt" };

	auto ifs = std::ifstream{ card_names};
	
	Util::check_stream(ifs, card_names,": does not exist.\n");

	std::filesystem::current_path("..\\..\\..\\..\\images");

	for (std::string s; ifs >> s;)
	{
		auto t = sf::Texture{};

		if (!t.loadFromFile(s))
		{
			throw Invalid_file{ "The file: " + s + " does not exist...\n" };
		}

		textures.emplace_back(t);
	} 

	auto img_size_x = 150 - 30;
	auto img_size_y = 90 - 30;

	for (auto i = 0, pos_x = 30; i <= img_size_x; i += pos_x)
	{
		for (auto j = 0, pos_y = 30; j <= img_size_y; j += pos_y)
		{
			auto t = sf::Texture{};

			if (!t.loadFromFile("..\\buttons\\buttons_clock_solitare.png", false, sf::IntRect{ sf::Vector2i{i,j},sf::Vector2i{pos_x,pos_y} }))
			{
				throw std::invalid_argument{ "Failed to load img...\n" };
			}

			textures.push_back(std::move(t));
		}
	}
}