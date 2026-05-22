#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "../headers/game.hpp"
#include "../headers/deck.hpp"
#include "../headers/board.hpp"
#include "../headers/time_status.hpp"

#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

sf::Clock clock1;

auto game() -> void
{
	sf::ContextSettings settings;
	settings.antiAliasingLevel = 16;

	// create the window
	sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "Clock Solitaire", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed, settings);
	window.setFramerateLimit(60);

	Deck de;
	Board b{ de };

	// run the program as long as the window is open
	while (window.isOpen())
	{
		//clock
		TimeStatus ts{ clock1 };

		// check all the window's events that were triggered since the last iteration of the loop

		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		// clear the window with black color
		window.clear(sf::Color{ 33,46,82 });

		//draw to window
		window.draw(b);
		window.draw(ts);

		// end the current frame
		window.display();
	}
}