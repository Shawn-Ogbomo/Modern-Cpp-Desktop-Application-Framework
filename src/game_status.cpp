#include <SFML/Graphics.hpp>

#include "../headers/game_status.hpp"
#include"../headers/exceptions.hpp"
#include"../headers/util.hpp"

Game_Status::Game_Status()
{
	Util::load_font(std::filesystem::path{ "..\\" }, font);

	game_id.setFont(font);
	game_id.setCharacterSize(26);
	game_id.setString(std::string{ "Game Id" }.append(11, ' ') + std::string{ ": " + std::to_string(Random_Number_Gen::g()) });
	game_id.setPosition(sf::Vector2f{ 0,696 });
	game_id.setFillColor(font_color);

	move.setFont(font);
	move.setCharacterSize(26);
	move.setString(std::string{ "Move" }.append(15, ' ') + ": " + std::to_string(move_count));
	move.setPosition(sf::Vector2f{ 0,748 });
	move.setFillColor(font_color);

	game_state.setFont(font);
	game_state.setCharacterSize(26);
	game_state.setString(std::string{ "State" }.append(16, ' ') + ": " + "Playing");
	game_state.setPosition(sf::Vector2f{ 0,722 });
	game_state.setFillColor(font_color);
}

void Game_Status::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(game_id);
	target.draw(move);
	target.draw(game_state);
}