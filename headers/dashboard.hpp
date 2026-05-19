#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class DashBoard : public sf::Drawable
{
	sf::Font font{ };
	sf::Color font_color{ 255, 250, 250 }; //fix
public:
	DashBoard();
	DashBoard(const DashBoard&) = delete;
	auto operator = (const DashBoard&)->DashBoard & = delete;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	//sf::Music song;
	//sf::Text song_name;

	sf::Text state{ font };			//playing, paused
	sf::Text game_id{ font };
	sf::Text move_count{ font };	//successful moves...
	sf::Text time{ font };

	sf::RectangleShape dash{ sf::Vector2f{ 1000.f,130.f } };
};

#endif // !DASHBOARD_HPP