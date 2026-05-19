#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "../headers/game.hpp"
#include "../headers/deck.hpp"
#include "../headers/board.hpp"
#include "../headers/dashboard.hpp"

#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

static auto show_elapsed(sf::Time& elapsed)
{
	auto h = std::chrono::duration_cast<std::chrono::hours>(static_cast<std::chrono::microseconds>(elapsed));
	elapsed -= h;

	auto m = std::chrono::duration_cast<std::chrono::minutes>(static_cast<std::chrono::microseconds>(elapsed));
	elapsed -= m;

	std::cout << h.count() << " hours: " << m.count() << " minutes: " << static_cast<int>(elapsed.asSeconds()) << " seconds\n";
	//draw this to the window
	//chrono literal of sf time object will hold hours minutes and seconds in dashboard
}

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
	DashBoard db{  };

	// run the program as long as the window is open
	while (window.isOpen())
	{
		//clock
		sf::Time elapsed = std::chrono::microseconds(clock1.getElapsedTime());
		auto h = std::chrono::duration_cast<std::chrono::hours>(static_cast<std::chrono::microseconds>(elapsed));
		elapsed -= h;

		auto m = std::chrono::duration_cast<std::chrono::minutes>(static_cast<std::chrono::microseconds>(elapsed));
		elapsed -= m;

		sf::Font font_test{ "../../../../fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf" };
		sf::Text elapsed_time{ font_test,std::to_string(h.count()) + " hours: " + std::to_string(m.count()) + " minutes: " + std::to_string(static_cast<int>(elapsed.asSeconds()))
			+ " seconds" };

		elapsed_time.setPosition(sf::Vector2f{ 0,770 });
		elapsed_time.setFillColor(sf::Color{ 63, 59, 147 });
		//std::cout << h.count() << " hours: " << m.count() << " minutes: " << static_cast<int>(elapsed.asSeconds()) << " seconds\n";
		//show_elapsed(elapsed);

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

		window.draw(b);
		window.draw(db);
		window.draw(elapsed_time);

		// end the current frame
		window.display();
	}
}