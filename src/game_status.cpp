#include "../headers/game_status.hpp"

Game_Status::Game_Status()
{
	game_id.setFont(font);
	game_id.setCharacterSize(26);
	game_id.setString("Game Id: #" + std::to_string(Random_Number_Gen::g()));
	game_id.setPosition(sf::Vector2f{ 0,670 });
	game_id.setFillColor(font_color);

	move_count.setFont(font);
	move_count.setCharacterSize(26);
	move_count.setString("Move: " + std::to_string(0));
	move_count.setPosition(sf::Vector2f{ 0,696 });
	move_count.setFillColor(font_color);

	game_state.setFont(font);
	game_state.setCharacterSize(26);
	game_state.setString("State: Playing");
	game_state.setPosition(sf::Vector2f{ 0,722 });
	game_state.setFillColor(font_color);
}