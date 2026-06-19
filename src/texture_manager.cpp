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
}