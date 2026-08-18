#ifndef GAME_STATUS_HPP
#define GAME_STATUS_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "state.hpp"
#include "random_number_gen.hpp"
///		TODO: Supply a call operator() overload to monitor the status of the game
///		This will update it in the dashboard, whether it is set to playing, paused, win, or lose
///		If the status is win or lose, render the correct text box to the screen
///		It will also check for the win condition as well
///		If the status in win, log it to database SQLTE
class Game_Status : public sf::Drawable
{
	sf::Font font;
public:
	Game_Status();
	Game_Status(const Game_Status&) = delete;
	auto operator = (const Game_Status&) -> Game_Status & = delete;
	Game_Status(Game_Status&&) = delete;
	auto operator = (Game_Status&&) -> Game_Status & = delete;
	auto operator++() ->const Game_Status&;
private:
	auto update() -> void;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Text move{ font };
	sf::Text game_id_t{ font };
	sf::Text game_state{ font };

	std::size_t game_id{};
	std::size_t move_count{};
};

#endif // GAME_STATUS_HPP