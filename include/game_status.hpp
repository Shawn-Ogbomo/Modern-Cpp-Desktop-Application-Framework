#ifndef GAME_STATUS_HPP
#define GAME_STATUS_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "state.hpp"
#include "random_number_gen.hpp"
///		TODO: Supply a call operator() overload to monitor the status of the game
///		This will update it in the dashboard, whether it is set to playing, paused, win, or lose
///		 If the status is win or lose, render the correct text box to the screen
///		 It will also check for the win condition as well
///		 If the status is win, log it to database SQLTE
///     Make Game_Status a friend class of Time_Status to access elapsed time and date in the Game_Status operator when writing to SQLITE....

/// Or make Game_Status operator a friend class of Time_status
/// Or make a free function to write to the database that takes both Game_Status and Time_Status...
class Game_Status : public sf::Drawable
{
	sf::Font font;
public:
	Game_Status();
	auto operator()(const Board::Piles& p, bool& pile_state) -> void;
	auto operator++() ->const Game_Status&;
private:
	auto update() -> void;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Text move{ font };
	sf::Text game_id_t{ font };
	sf::Text game_state{ font };

	std::size_t game_id{};
	std::size_t move_count{ };
	Game_State state{};
};

#endif // GAME_STATUS_HPP