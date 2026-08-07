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

struct DashBoard : sf::Drawable
{
public:
	DashBoard()
	{
		dash.setFillColor(sf::Color{ 228, 193, 156 });
		dash.setPosition(sf::Vector2f{ 0.f,770.f });
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
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

class Application
{
public:
	Application()
	{
		if (!sf::Shader::isAvailable())
		{
			throw std::runtime_error{ "Shaders are not supported on this GPU...\n" };
		}

		if (std::filesystem::path shader = { "../../../../assets/shader/effect.frag" }; !glow_shader.loadFromFile(shader, sf::Shader::Type::Fragment))
		{
			throw std::invalid_argument{ "\nFailed to load shader: " + shader.filename().string() + "\n in path: " + shader.parent_path().string() + "\n" };
		}

		static const sf::Texture dummyTexture(sf::Vector2u(1, 1));

		auto innerSize = sf::Vector2f(96, 144);

		auto glowWidth = 10.f;

		auto outerSize = sf::Vector2f{ innerSize + sf::Vector2f(glowWidth * 2 , glowWidth * 2) };

		glow_rect.setSize(outerSize);

		glow_rect.setTexture(&dummyTexture);		// Forces SFML to supply UV map coordinates

		auto ratioX = innerSize.x / outerSize.x;
		auto ratioY = innerSize.y / outerSize.y;

		glow_shader.setUniform("u_glowRatioX", ratioX);
		glow_shader.setUniform("u_glowRatioY", ratioY);

		auto parchment_white = sf::Color{ 240, 245, 245 };

		glow_shader.setUniform("u_glowColor", sf::Glsl::Vec4(
			parchment_white.r / 255.f,
			parchment_white.g / 255.f,
			parchment_white.b / 255.f,
			parchment_white.a / 255.f));

		window.setFramerateLimit(60);
		settings.antiAliasingLevel = 15;
		window.setVerticalSyncEnabled(true);
		window.setMouseCursor(cursor.value());
		window.setIcon(sf::Image{ std::filesystem::path{"../../../../assets/icon/7_diamonds_new.png"} });
	}

	auto run() -> void
	{
		auto de = Deck{};
		auto b = Board{ de };
		auto db = DashBoard{};

		auto card = std::end(b.piles);
		auto destination_pile = std::end(b.piles);
		
		// run the program as long as the window is open
		while (window.isOpen())
		{
			db.mp(window);

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

				else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
				{
					if (card != std::end(b.piles))
					{
						card->second.back().first.img().first.setPosition(sf::Vector2f{ static_cast<float>(mouseMoved->position.x),static_cast<float>(mouseMoved->position.y) });
						card->second.back().first.img().second.setPosition(sf::Vector2f{ static_cast<float>(mouseMoved->position.x),static_cast<float>(mouseMoved->position.y) });
					}
				}

				else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
				{
					if (mouseButtonReleased->button == sf::Mouse::Button::Left && card != std::end(b.piles))
					{
						//if it is dropped in the correct destination pile
						// add it to the front of the queue std::move
						// pop the moved from card from its original pile
						// flip back card face up in destination pile
						// turn off active pile of the moved from pile
						// turn on active on the new destination pile
						// if the back card has the same value as the destination pile
						// move it to the front
						// set new back card face up
						// keep active pile on current pile
						//
						// if a card is already face up in dest pile and move from object value matched dest pile
						// move both cards to the back and flip new back card face up
						// change active pile to new dest
						// turn prov active off
						//
						//
						//
						// if button left click is released while dragging card, and it is not dropped on the correct destination pile, return it to its original position...
					/*	card->second.back().first.img().first.setPosition(sf::Vector2f{ 452, 313 });
						card->second.back().first.img().second.setPosition(sf::Vector2f{ 452, 313 });*/
						//card = std::end(b.piles);
					}
				}

				else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
				{
					if (mouseButtonPressed->button == sf::Mouse::Button::Left)
					{
						auto cursor_pos = sf::Vector2f{ static_cast<float>(sf::Mouse::getPosition(window).x), static_cast<float>(sf::Mouse::getPosition(window).y) };
						db.mp(window, cursor_pos);
						card = b(card, cursor_pos);
					}
				}
			}

			//what if we start with a king in the middle
				// we have to swap it
				//
				//
			//check win cond here....
				//4 kings face up in the middle
					//all cards face up?
						//win
					//lose

			// clear the window with blue color
			window.clear(sf::Color{ 33,46,82 });

			//draw to window
			window.draw(db);

			if (destination_pile = b(card); destination_pile != std::end(b.piles) && destination_pile->second.back().second == card->second.back().first.value())
			{
				auto pos = destination_pile->second.back().first.img().first.getPosition();
				glow_rect.setPosition(sf::Vector2f{ pos.x - 10,pos.y - 10 });
				window.draw(glow_rect,&glow_shader);
			}

			window.draw(b);
			
			// end the current frame
			window.display();
		}
	}
private:
	sf::RenderWindow			 window{ sf::VideoMode({ 1000, 900 }), "Clock Solitaire", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed };
	sf::ContextSettings		     settings;
	sf::Shader						 glow_shader{ std::filesystem::path{"../../../../assets/shader/effect.frag"}, sf::Shader::Type::Fragment };
	sf::Image						 cursor_image{ std::filesystem::path{"../../../../assets/cursor/cursor_ice_white.png"} };
	std::optional<sf::Cursor> cursor = sf::Cursor::createFromPixels(cursor_image.getPixelsPtr(), sf::Vector2u{ 10,10 }, sf::Vector2u{ 0,0 });
	sf::RectangleShape			 glow_rect;
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