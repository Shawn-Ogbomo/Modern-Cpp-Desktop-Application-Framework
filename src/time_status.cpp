#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include"../headers/util.hpp"
#include "../headers/exceptions.hpp"
#include "../headers/time_status.hpp"
#include"../headers/random_number_gen.hpp"

TimeStatus::TimeStatus(sf::Clock& c)
{
	Util::load_font(std::filesystem::path{ "..\\" + std::string{"fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf"} }, font);

	dash.setFillColor(sf::Color{ 228, 193, 156 });
	dash.setOrigin(sf::Vector2f{ 0.f,0.f });
	dash.setPosition(sf::Vector2f{ 0.f,700.f });

	date.setFont(font);
	date.setCharacterSize(26);

	std::time_t result = std::time(nullptr);
	std::string date_today = (std::ctime(&result));

	date.setString("Date: " + date_today);
	date.setPosition(sf::Vector2f{ 600,774 });
	date.setFillColor(sf::Color{ 63, 59, 147 });

	sf::Time elapsed = std::chrono::microseconds(c.getElapsedTime());

	auto h = std::chrono::duration_cast<std::chrono::hours>(static_cast<std::chrono::microseconds>(elapsed));
	elapsed -= h;

	auto m = std::chrono::duration_cast<std::chrono::minutes>(static_cast<std::chrono::microseconds>(elapsed));
	elapsed -= m;

	elapsed_time.setFont(font);
	elapsed_time.setCharacterSize(26);

	elapsed_time.setString("Elapsed Time: " + std::to_string(h.count()) + " hours: " + std::to_string(m.count()) + " minutes: " + std::to_string(static_cast<int>(elapsed.asSeconds()))
		+ " seconds");
	elapsed_time.setPosition(sf::Vector2f{ 0,774 });
	elapsed_time.setFillColor(sf::Color{ 63, 59, 147 });
}

void TimeStatus::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(dash);
	target.draw(date);
	target.draw(elapsed_time);
}