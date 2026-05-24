#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <string>
#include <ctime>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class TimeStatus : public sf::Drawable
{
	sf::Font font{ };
	sf::Color font_color{ sf::Color{63, 59, 147} };
public:
	TimeStatus(sf::Clock& c);
	TimeStatus(const TimeStatus&) = delete;
	auto operator = (const 	TimeStatus&)->TimeStatus & = delete;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Text date{ font };
	sf::Text elapsed_time{ font };
	sf::RectangleShape dash{ sf::Vector2f{ 1000.f,130.f } };
};

#endif // !DASHBOARD_HPP