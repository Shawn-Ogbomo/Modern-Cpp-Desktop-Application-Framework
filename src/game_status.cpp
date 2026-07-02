#include <SFML/Graphics.hpp>

#include "../include/game_status.hpp"
#include"../include/exceptions.hpp"
#include"../include/util.hpp"

Game_Status::Game_Status()
	:game_id{ Random_Number_Gen::g() }
{
	Util::load_font(std::filesystem::path{ "..\\" + std::string{"fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf"} }, font);

	game_id_t.setFont(font);
	game_id_t.setCharacterSize(26);
	game_id_t.setString(std::string{ "Game Id" }.append(11, ' ') + std::string{ ": " + std::to_string(game_id) });
	game_id_t.setPosition(sf::Vector2f{ 0,790 });
	game_id_t.setFillColor(sf::Color{ 63, 59, 147 });

	move.setFont(font);
	move.setCharacterSize(26);
	move.setString(std::string{ "Move" }.append(15, ' ') + ": " + std::to_string(move_count));
	move.setPosition(sf::Vector2f{ 0,842 });
	move.setFillColor(sf::Color{ 63, 59, 147 });

	game_state.setFont(font);
	game_state.setCharacterSize(26);
	game_state.setString(std::string{ "State" }.append(16, ' ') + ": " + "Playing");
	game_state.setPosition(sf::Vector2f{ 0,816 });
	game_state.setFillColor(sf::Color{ 63, 59, 147 });
}

void Game_Status::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(game_id_t);
	target.draw(move);
	target.draw(game_state);
}