#include <SFML/Graphics.hpp>

#include "../headers/game_status.hpp"
#include"../headers/exceptions.hpp"

Game_Status::Game_Status()
{
	std::filesystem::path root{ "..\\..\\..\\..\\" };

	if (!font.openFromFile(root.string() + "fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf"))
	{
		throw Invalid_file{ "The file does not exist...\n" };
	}

	game_id.setFont(font);
	game_id.setCharacterSize(26);
	game_id.setString("Game Id: #" + std::to_string(Random_Number_Gen::g()));
	game_id.setPosition(sf::Vector2f{ 0,670 });
	game_id.setFillColor(font_color);

	move.setFont(font);
	move.setCharacterSize(26);
	move.setString("Move: " + std::to_string(move_count));
	move.setPosition(sf::Vector2f{ 0,696 });
	move.setFillColor(font_color);

	game_state.setFont(font);
	game_state.setCharacterSize(26);
	game_state.setString("State: Playing");
	game_state.setPosition(sf::Vector2f{ 0,722 });
	game_state.setFillColor(font_color);
}

void Game_Status::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(game_id);
	target.draw(move);
	target.draw(game_state);
}