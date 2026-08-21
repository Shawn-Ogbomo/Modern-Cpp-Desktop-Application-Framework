#include <SFML/Graphics.hpp>

#include"../include/util.hpp"
#include"../include/exceptions.hpp"
#include "../include/game_status.hpp"
#include"../include/directory_manager.hpp"

namespace rng = std::ranges;

Game_Status::Game_Status()
	:game_id{ Random_Number_Gen::g() }
{
	Util::load_font(std::filesystem::path{ Directory_Manager::assets_dir() / "fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf" }, font);

	game_id_t.setFont(font);
	game_id_t.setCharacterSize(26);
	game_id_t.setString(std::string{ "Game Id" }.append(11, ' ') + ": " + std::to_string(game_id));
	game_id_t.setPosition(sf::Vector2f{ 0,790 });
	game_id_t.setFillColor(sf::Color{ 63, 59, 147 });

	move.setFont(font);
	move.setCharacterSize(26);

	update();

	move.setPosition(sf::Vector2f{ 0,842 });
	move.setFillColor(sf::Color{ 63, 59, 147 });

	game_state.setFont(font);
	game_state.setCharacterSize(26);
	game_state.setString(std::string{ "State" }.append(16, ' ') + ": " + "Playing");
	game_state.setPosition(sf::Vector2f{ 0,816 });
	game_state.setFillColor(sf::Color{ 63, 59, 147 });
}

auto::Game_Status::update() -> void
{
	move.setString(std::string{ "Move" }.append(15, ' ') + ": " + std::to_string(move_count));
}

/// TODO: start with the win condition...
///			Render the win message to the screen -- text box with a play again and quit option. P
///			prompt user  to log their win to the database 3 character alias for their name
///		end if
///
/// render the you lose message to the screen with a play again and quit screen
///		Pause the game while text box is active
///		Add pause, resume, and help -- list game objective functionality

auto::Game_Status::operator()(const Board::Piles& p) ->void
{
	const auto& lose_condition = [](auto c) -> int {
		return c.value() == Rank_Lib::Rank::king && c.position() == Card_State::face_up; };

	if (move_count == Board::cards_pile * Board::total_piles)
	{
		///change state to win and halt all UI  functions 
		std::cout << "You win...\n";
	}

	///Why is an extra move for this to execute.
	///Debug for when you are moving the last king into the middle pile.
	else if (auto num_kings = std::count_if(std::get<1>(p.back()).begin(), std::get<1>(p.back()).end(), lose_condition); num_kings == Board::cards_pile)
	{
		std::cout << "There are 4 kings in the middle...\n";
	}
}

auto::Game_Status::operator++() ->const Game_Status&
{
	++move_count;
	update();
	return *this;
}
void Game_Status::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(game_id_t);
	target.draw(move);
	target.draw(game_state);
}