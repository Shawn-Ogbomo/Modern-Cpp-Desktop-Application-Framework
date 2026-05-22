#ifndef GAME_STATUS_HPP
#define GAME_STATUS_HPP

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

#include "state.hpp"
#include "random_number_gen.hpp"

struct Game_Status : public sf::Drawable
{
	//Objects should be shared among Game_Status and Time_Status
	sf::Font font{ };
	sf::Color font_color{ sf::Color{63, 59, 147} };
public:
	Game_Status();
	Game_Status(const Game_Status&) = delete;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::Text game_id{ font };
	sf::Text move{ font };
	sf::Text game_state{ font };

	std::size_t move_count{};
};

#endif // !GAME_STATUS_HPP