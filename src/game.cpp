#include <chrono>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "../headers/deck.hpp"
#include "../headers/game.hpp"
#include "../headers/board.hpp"
#include "../headers/time_status.hpp"
#include "../headers/game_status.hpp"
#include "../headers/music_player.hpp"

sf::Clock clock1;

struct DashBoard : sf::Drawable
{
public:
	DashBoard::DashBoard()
	{
		dash.setFillColor(sf::Color{ 228, 193, 156 });
		dash.setPosition(sf::Vector2f{ 0.f,770.f });
	}

	virtual void DashBoard::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(dash);
		target.draw(gs);
		target.draw(ts);
		target.draw(mp);
	}

	Game_Status gs;
	Time_Status ts{ clock1 };
	Music_Player mp;
	sf::RectangleShape dash{ sf::Vector2f{ 1000.f,130.f } };
};

auto game() -> void
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 16;

	// create the window
	sf::RenderWindow window(sf::VideoMode({ 1000, 900 }), "Clock Solitaire", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed, settings);
	window.setFramerateLimit(60);

	auto de = Deck{};
	auto b =Board { de };
	auto db = DashBoard{};

	db.mp.play();
	// run the program as long as the window is open

	while (window.isOpen())
	{
		//clock
		db.ts.update(clock1);

		// check all the window's events that were triggered since the last iteration of the loop
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		// clear the window with blue color
		window.clear(sf::Color{ 33,46,82 });

		//draw to window
		window.draw(b);
		window.draw(db);

		// end the current frame
		window.display();
	}
}