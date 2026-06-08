#include <fstream>
#include <filesystem>

#include "../headers/util.hpp"
#include "../headers/texture_manager.hpp"

auto Texture_manager::load_textures() ->void
{
	auto ifs = std::ifstream{ "\\clock_solitaire\\txt\\card_names.txt" };
	
	Util::check_stream(ifs, "Invalid file...\n");

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