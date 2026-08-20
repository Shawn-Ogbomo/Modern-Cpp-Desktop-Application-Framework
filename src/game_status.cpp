#include <SFML/Graphics.hpp>

#include"../include/util.hpp"
#include"../include/exceptions.hpp"
#include "../include/game_status.hpp"
#include"../include/directory_manager.hpp"

namespace rng = std::ranges;

Game_Status::Game_Status()
	:game_id{ Random_Number_Gen::g() }
{
	Util::load_font(std::filesystem::path{ Directory_Manager::assets_dir()/"fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf" }, font);

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
/// If there are 4 kings and they are face-up in the king pile 
///		 If all of the cards are face up -- use std::ranges::all_of 
///			Render the win message to the screen -- text box with a play again and quit option. P
///			prompt user if they want to log their win to the database have them enter 3 character alias for their name
///		end if 
///		
/// render the you lose message to the screen with a play again and quit screen 
///		Add pause, resume, and help -- list game objective functionality

/// This is inefficient
/// use the move count to detect if the cards are face up -1 from the total since move 0 a card is face up 
/// every time you increment move count a card is face up since the move is valid 
/// there are 52 cards in the deck total, therefore, the count would have to be 52 for all the cards to be face up 
/// once the count is 52 check get the king pile and see if there are 4 kings there. we don't have to check for the position since we are tracking face up cards with the move count
/// 
/// get iterator to king pile 
/// if count is 52, you win 
/// 
/// if count is not 52 get the count of kings in the king pile 
auto::Game_Status::operator()(const Board::Piles &p) ->void
{
	if (move_count == (Board::cards_pile * Board::total_piles)-1)
	{
		std::cout << "You win...\n";
		return;
	}

	/// You should get a reference to the king pile from the outside of the main function.
	///So you can get 0(1) time complexity instead of doing a find for a king pile that has a mutable position...
	/// Then get the count of the amount of kings in the pile to determine if the player has lost or if they're still playing...
	/// std::count is 0(N)
	/// find an efficient way to determine loss
	auto win = find_if(p.begin(), p.end(), [&p](auto pile) {
		auto stack = std::get<1>(pile); 
		return std::get<2>(pile) == Rank_Lib::Rank::king
			&& std::all_of(stack.begin(), stack.end(), [](auto c) {return c.value() == Rank_Lib::Rank::king && c.position() == Card_State::face_up; });
		});

	if (win != std::end(p))
	{
		if (auto num_kings = std::count_if(std::get<1>(*win).begin(), std::get<1>(*win).end(), [](auto internal_c) 
			{ return internal_c.value() == Rank_Lib::Rank::king; });num_kings ==4)
		{
			std::cout << "\n\nThere are 4 kings in the middle..\n\n";
		}
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