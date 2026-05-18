#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "../headers/game.hpp"
#include "../headers/deck.hpp"
#include "../headers/board.hpp"

#include <iostream>
#include <chrono>

sf::Clock clock1;

auto game() -> void
{
	// create the window
	sf::RenderWindow window(sf::VideoMode({ 1000, 800 }), "Clock Solitaire", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	Deck de;

	Board b{ de };

	// run the program as long as the window is open
	while (window.isOpen())
	{
		//clock
		sf::Time elapsed = clock1.getElapsedTime();
		//s = elapsed.asSeconds();
		//std::cout << std::chrono::duration_cast<std::chrono::minutes>(s).count() << " minutes\n";
		//std::cout << "H " << h << ": " << "M " << m << ": " << "S " << s << "\n";

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

		// draw to the screen here...
		for (size_t i = 0; i < Board::total_piles; ++i)
		{
			auto sz = b.piles[i].size();

			for (size_t j = 0; j < sz; ++j)
			{
				const auto& [card, rank] = b.piles[i][j];
				window.draw(card);
			}
		}

		// end the current frame
		window.display();
	}
}