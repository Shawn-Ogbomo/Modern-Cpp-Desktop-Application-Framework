#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include <format>

#include"../include/util.hpp"
#include "../include/exceptions.hpp"
#include "../include/time_status.hpp"
#include"../include/random_number_gen.hpp"

auto Time_Status::update(sf::Clock& c) ->void
{
	auto elapsed = sf::Time{ std::chrono::microseconds(c.getElapsedTime()) };

	h = std::chrono::duration_cast<std::chrono::hours>(static_cast<std::chrono::microseconds>(elapsed));
	elapsed -= h;

	m = std::chrono::duration_cast<std::chrono::minutes>(static_cast<std::chrono::microseconds>(elapsed));
	elapsed -= m;

	s = std::chrono::duration_cast<std::chrono::seconds>(static_cast<std::chrono::microseconds>(elapsed));

	elapsed_time.setString("Elapsed Time: " + std::to_string(h.count()) + " hours: " + std::to_string(m.count()) + " minutes: " + std::to_string(s.count())
		+ " seconds");

	date.setString("Date: " + Util::local_time());
}

Time_Status::Time_Status(sf::Clock& c)
{
	Util::load_font(std::filesystem::path{"fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf"}, font);

	update(c);

	elapsed_time.setFont(font);
	elapsed_time.setCharacterSize(26);
	elapsed_time.setPosition(sf::Vector2f{ 0,871 });
	elapsed_time.setFillColor(sf::Color{ 63, 59, 147 });

	date.setFont(font);
	date.setCharacterSize(26);
	date.setPosition(sf::Vector2f{ 600,871 });
	date.setFillColor(sf::Color{ 63, 59, 147 });
}

void Time_Status::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(date);
	target.draw(elapsed_time);
}