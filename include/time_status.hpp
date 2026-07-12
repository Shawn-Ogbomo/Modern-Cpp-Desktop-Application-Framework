#ifndef TIME_STATUS_HPP
#define TIME_STATUS_HPP

#include <string>
#include <ctime>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class Time_Status : public sf::Drawable
{
	sf::Font font;
public:
	explicit Time_Status(sf::Clock& c);
	Time_Status(const Time_Status&) = delete;
	auto operator = (const 	Time_Status&)->Time_Status & = delete;
	Time_Status(const Time_Status&&) = delete;
	auto operator = (const 	Time_Status&&)->Time_Status & = delete;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	auto update(sf::Clock& c) -> void;
private:
	sf::Text date{ font };
	sf::Text elapsed_time{ font };

	std::string date_today;

	std::chrono::hours h{};
	std::chrono::minutes m{};
	std::chrono::seconds s{};
};

#endif // TIME_STATUS_HPP