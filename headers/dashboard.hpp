//sf::RectangleShape rectangle{ sf::Vector2f{265.f,140.f} };
//rectangle.setFillColor(sf::Color{ 246, 220, 175 });
//rectangle.setOutlineThickness(5.f);
//rectangle.setOutlineColor(sf::Color(133, 27, 19));
//
//
//rectangle.setOrigin(sf::Vector2f{ 120,0 });
//rectangle.setPosition(sf::Vector2f{ 130.107,645.277 });
//window.draw(rectangle);

#ifndef DASHBOARD_HPP
#define DASHBOARD_HPP

#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class DashBoard : public sf::Drawable
{
	sf::Font font;
	sf::Color font_color{ 255, 250, 250 };
public:
	DashBoard();
	DashBoard(const DashBoard&) = delete;
	auto operator = (const DashBoard&)->DashBoard & = delete;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::Music song;
	sf::Text song_name;

	sf::Text move_count;

	sf::Clock elapsed_time;
	sf::RectangleShape dash;
};

#endif // !DASHBOARD_HPP