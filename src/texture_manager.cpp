#include <utility>
#include <fstream>
#include <filesystem>

#include "../include/util.hpp"
#include "../include/texture_manager.hpp"

auto Card_Manager::load_textures() ->void
{
	auto card_names = std::filesystem::path{ "../../../../assets/txt/card_names.txt" };

	auto ifs = std::ifstream{ card_names };

	Util::check_stream(ifs, card_names, ": does not exist.\n");

	std::filesystem::current_path("../../../../assets/images");

	for (std::string s; ifs >> s;)
	{
			textures.emplace_back(sf::Texture{s,false});
	}
}

auto Button_Manager::load_textures() ->void
{
	const auto buttons = sf::Image{ "../buttons/buttons_clock_solitare.png" };
	const auto dimmensions_button = sf::Vector2i{ 30,30 };
	const auto dimmensions_image = sf::Vector2i{ static_cast<sf::Vector2i>(buttons.getSize()) - dimmensions_button };

	   auto t = [&](auto x, int y = 0) ->std::tuple<sf::Texture, sf::Texture, sf::Texture> {
		
		return std::make_tuple(
			sf::Texture{ buttons,false,{ sf::Vector2i{x,y}, dimmensions_button} }, 
			sf::Texture{ buttons,false,{ sf::Vector2i{x,(y + dimmensions_button.y)},dimmensions_button } },
			sf::Texture{ buttons,false,{ sf::Vector2i{x,(y + (dimmensions_button.y  * 2) )},dimmensions_button } });};

	for (auto i = 0;  i <= dimmensions_image.x; i += dimmensions_button.x)
	{
		textures.emplace_back(t(i));
	}
}