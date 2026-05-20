#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>

#include "../headers/dashboard.hpp"
#include "../headers/exceptions.hpp"
#include"../headers/random_number_gen.hpp"

DashBoard::DashBoard(sf::Clock& c)
{
	//replace the directory separators with
	// path::preferred_separator

	if (!font.openFromFile("../../../../fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf"))
	{
		throw Invalid_file{ "The file does not exist...\n" };
	}

	dash.setFillColor(sf::Color{ 228, 193, 156 });
	dash.setOrigin(sf::Vector2f{ 0.f,0.f });
	dash.setPosition(sf::Vector2f{ 0.f,700.f });

	game_id.setFont(font);
	game_id.setCharacterSize(26);
	game_id.setString("Game Id: #" + std::to_string(Random_Number_Gen::g()));
	game_id.setPosition(sf::Vector2f{ 0,670 });
	game_id.setFillColor(font_color);

	move_count.setFont(font);
	move_count.setCharacterSize(26);
	move_count.setString("Move: " + std::to_string(0));
	move_count.setPosition(sf::Vector2f{ 0,696 });
	move_count.setFillColor(font_color);

	state.setFont(font);
	state.setCharacterSize(26);
	state.setString("State: Playing");
	state.setPosition(sf::Vector2f{ 0,722 });
	state.setFillColor(font_color);

	date.setFont(font);
	date.setCharacterSize(26);

	std::time_t result = std::time(nullptr);
	std::string date_today = (std::ctime(&result));

	date.setString(date_today);
	date.setPosition(sf::Vector2f{ 0,748 });
	date.setFillColor(font_color);

	sf::Time elapsed = std::chrono::microseconds(c.getElapsedTime());

	auto h = std::chrono::duration_cast<std::chrono::hours>(static_cast<std::chrono::microseconds>(elapsed));
	elapsed -= h;

	auto m = std::chrono::duration_cast<std::chrono::minutes>(static_cast<std::chrono::microseconds>(elapsed));
	elapsed -= m;

	elapsed_time.setFont(font);
	elapsed_time.setCharacterSize(26);

	elapsed_time.setString(std::to_string(h.count()) + " hours: " + std::to_string(m.count()) + " minutes: " + std::to_string(static_cast<int>(elapsed.asSeconds()))
		+ " seconds");
	elapsed_time.setPosition(sf::Vector2f{ 0,774 });
	elapsed_time.setFillColor(sf::Color{ font_color });
}

void DashBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(dash);
	target.draw(game_id);
	target.draw(move_count);
	target.draw(state);
	target.draw(date);
	target.draw(elapsed_time);
}