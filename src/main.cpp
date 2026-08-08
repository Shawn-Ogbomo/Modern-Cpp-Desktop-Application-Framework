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

namespace
{
	std::filesystem::path assets_dir()
	{
#ifdef SFML_SYSTEM_IOS
		return "";
#else
		return "../../../../assets/";
#endif
	}
}

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

		if (std::filesystem::path shader = { assets_dir() / "shader/effect.frag" }; !glow_shader.loadFromFile(shader, sf::Shader::Type::Fragment))
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
		window.setIcon(sf::Image{assets_dir() / "icon/7_diamonds_new.png"} );
	}

	auto enable_shader(const Board& b) ->void
	{
		if (b.destination_pile != std::end(b.piles) && b.source_pile != std::end(b.piles)
			&& b.destination_pile->second.back().second == b.source_pile->second.back().first.value())
		{
			const auto pos = b.destination_pile->second.front().first.img().first.getPosition();
			glow_rect.setPosition(sf::Vector2f{ pos.x - 10,pos.y - 10 });
			window.draw(glow_rect, &glow_shader);
		}
	}

	auto run() -> void
	{
		auto de = Deck{};
		auto b = Board{ de };
		auto db = DashBoard{};

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
					if (b.source_pile != std::end(b.piles))
					{
						const auto pos = sf::Vector2f{ mouseMoved->position.x + .0f, mouseMoved->position.y + .0f };
						b.source_pile->second.back().first.img().first.setPosition(pos);
						b.source_pile->second.back().first.img().second.setPosition(pos);
						b.destination_pile = b(b.source_pile,b.destination_pile,b.source_pile->second.back().first.img().first.getPosition());
					}
				}

				else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
				{
					if (mouseButtonReleased->button == sf::Mouse::Button::Left && b.source_pile != std::end(b.piles))
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
						b.source_pile->second.back().first.img().first.setPosition(sf::Vector2f{ 452, 313 });
						b.source_pile->second.back().first.img().second.setPosition(sf::Vector2f{ 452, 313 });
						b.source_pile= std::end(b.piles);
					}
				}

				else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
				{
					if (mouseButtonPressed->button == sf::Mouse::Button::Left)
					{
						auto cursor_pos = sf::Vector2f{ sf::Mouse::getPosition(window).x + .0f, sf::Mouse::getPosition(window).y + .0f};
						db.mp(window, cursor_pos);
						b.source_pile = b(b.source_pile,b.destination_pile,cursor_pos);
					}
				}
			}

			// clear the window with blue color
			window.clear(sf::Color{ 33,46,82 });

			//draw to window
			window.draw(db);
			
			enable_shader(b);
			
			window.draw(b, &glow_shader);
			
			// end the current frame
			window.display();
		}
	}
private:
	sf::RenderWindow			 window{ sf::VideoMode({ 1000, 900 }), "Clock Solitaire", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed };
	sf::ContextSettings		     settings;
	sf::Shader						 glow_shader{ std::filesystem::path{assets_dir() / "shader/effect.frag"}, sf::Shader::Type::Fragment };
	sf::Image						 cursor_image{ std::filesystem::path{assets_dir() / "cursor/cursor_ice_white.png"} };
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