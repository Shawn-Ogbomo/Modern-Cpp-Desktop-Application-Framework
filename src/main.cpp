#include <chrono>
#include <fstream>
#include <iterator>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "../include/util.hpp"
#include "../include/deck.hpp"
#include "../include/board.hpp"
#include "../include/exceptions.hpp"
#include "../include/time_status.hpp"
#include "../include/game_status.hpp"
#include "../include/music_player.hpp"

sf::Clock clock1;

class Application
{
public:
	Application()
	{
		if (!sf::Shader::isAvailable())
		{
			throw std::runtime_error{ "Shaders are not supported on this GPU...\n" };
		}

		window.setFramerateLimit(60);
		settings.antiAliasingLevel = 15;
		window.setVerticalSyncEnabled(true);
		window.setMouseCursor(cursor.value());
		window.setIcon(sf::Image{ std::filesystem::path{"..\\..\\..\\..\\assets\\icon\\7_diamonds_new.png"} });
	}

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

	auto run() -> void
	{
		auto de = Deck{};
		auto b = Board{ de };
		auto db = DashBoard{};
	
		// run the program as long as the window is open
		while (window.isOpen())
		{
			db.mp(clock1, window);
			
			db.ts.update(clock1);

			// check all the window's events that were triggered since the last iteration of the loop
			while (const std::optional event = window.pollEvent())
			{
				if (event->is<sf::Event::Closed>())
				{
					window.close();
				}

				if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
				{
					if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
						window.close();
				}

				else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
				{
					if (mouseButtonPressed->button == sf::Mouse::Button::Left)
					{
						auto cursor_pos = sf::Vector2f{ static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y) };
						db.mp(clock1, window, cursor_pos);
					}
				}

				else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
				{
					if (mouseButtonReleased->button == sf::Mouse::Button::Left)
					{
					}
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
private:
	sf::RenderWindow			 window{ sf::VideoMode({ 1000, 900 }), "Clock Solitaire", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed };
	sf::ContextSettings		     settings;
	sf::Shader					     glow_shader{ std::filesystem::path{"..\\..\\..\\..\\assets\\shader\\effect.frag"}, sf::Shader::Type::Fragment };
	sf::Image						 cursor_image{ std::filesystem::path{"..\\..\\..\\..\\assets\\cursor\\cursor_ice_white.png"} };
	std::optional<sf::Cursor> cursor = sf::Cursor::createFromPixels(cursor_image.getPixelsPtr(), sf::Vector2u{ 10,10 }, sf::Vector2u{ 0,0 });
};

auto main() -> int
{
	try
	{
		Application application;
		application.run();
	}

	catch (const sf::Exception& e)
	{
		std::cerr << e.what() << "\n";
		return 1;
	}

	catch (std::exception& e)
	{
		std::cerr << e.what() << "\n";
		return 2;
	}
}