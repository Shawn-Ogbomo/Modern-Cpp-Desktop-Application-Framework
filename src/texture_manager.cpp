#include <utility>
#include <fstream>
#include <filesystem>

#include "../include/util.hpp"
#include "../include/texture_manager.hpp"

auto Texture_manager::load_textures() ->void
{
	auto card_names = std::filesystem::path{ "../../../../assets/txt/card_names.txt" };

	auto ifs = std::ifstream{ card_names };

	Util::check_stream(ifs, card_names, ": does not exist.\n");

	std::filesystem::current_path("../../../../assets/images");

	for (std::string s; ifs >> s;)
	{
			textures.emplace_back(sf::Texture{s,false});
	}

	const auto buttons = sf::Image{ "../buttons/buttons_clock_solitare.png" };
	const auto dimmensions_button = sf::Vector2i{ 30,30 };
	const auto dimmensions_image = sf::Vector2i{ static_cast<sf::Vector2i>(buttons.getSize()) - dimmensions_button };

	for (auto i = 0, pos_x = dimmensions_button.x; i <= dimmensions_image.x; i += pos_x)
	{
		for (auto j = 0, pos_y = dimmensions_button.y; j <= dimmensions_image.y; j += pos_y)
		{
			textures.push_back(sf::Texture{ buttons,false,{ sf::Vector2i{i,j},sf::Vector2i{pos_x,pos_y} } });
		}
	}
}