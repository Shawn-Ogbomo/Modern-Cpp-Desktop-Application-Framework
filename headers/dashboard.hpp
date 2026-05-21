#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <string>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <ctime>

class DashBoard : public sf::Drawable
{
	sf::Font font{ };
	sf::Color font_color{ sf::Color{63, 59, 147} };
public:
	DashBoard(sf::Clock& c);
	DashBoard(const DashBoard&) = delete;
	auto operator = (const DashBoard&)->DashBoard & = delete;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Text game_id{ font };
	sf::Text move_count{ font };
	sf::Text state{ font };
	sf::Text date{ font };
	sf::Text elapsed_time{ font };
	sf::RectangleShape dash{ sf::Vector2f{ 1000.f,130.f } };
};

#endif // !DASHBOARD_HPP