#ifndef GAME_STATUS_HPP
#define GAME_STATUS_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "state.hpp"
#include "random_number_gen.hpp"

class Game_Status
{
	sf::Font font{ };
public:
	Game_Status();
	Game_Status(const Game_Status&) = delete;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Text game_id{ font };
	sf::Text move_count{ font };
	sf::Text game_state{ font };

	State_lib::Game_state state{};
};

#endif // !GAME_STATUS_HPP