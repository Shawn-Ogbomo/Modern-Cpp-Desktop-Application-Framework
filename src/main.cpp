#include <chrono>
#include <fstream>
#include <iterator>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include "../include/util.hpp"
#include "../include/deck.hpp"
#include "../include/board.hpp"
#include "../include/dash_board.hpp"
#include "../include/time_status.hpp"
#include "../include/game_status.hpp"
#include "../include/music_player.hpp"
#include "../include/directory_manager.hpp"

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

		if (std::filesystem::path shader = { Directory_Manager::assets_dir() / "shader/effect.frag" }; !glow_shader.loadFromFile(shader, sf::Shader::Type::Fragment))
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
		window.setIcon(sf::Image{ Directory_Manager::assets_dir() / "icon/7_diamonds_new.png" });
	}

	auto enable_shader(const Board& b) -> void
	{
		if (b.destination_pile != std::end(b.piles) && b.source_pile != std::end(b.piles)
			&& std::get<2>(*b.destination_pile) == std::get<1>(*b.source_pile).back().value())
		{
			const auto pos = std::get<1>(*b.destination_pile).front().img().first.getPosition();
			glow_rect.setPosition(sf::Vector2f{ pos.x - 10,pos.y - 10 });
			window.draw(glow_rect, &glow_shader);
			shader_enabled = true;
			return;
		}

		shader_enabled = false;
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
					{
						window.close();
					}
				}

				else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
				{
					if (b.source_pile != std::end(b.piles))
					{
						b.update_position(std::get<1>(*b.source_pile).back().img(), sf::Vector2f{ mouseMoved->position.x + .0f, mouseMoved->position.y + .0f });
						b();
					}
				}

				else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
				{
					if (mouseButtonReleased->button == sf::Mouse::Button::Left && b.source_pile != std::end(b.piles))
					{
						if (!shader_enabled)
						{
							b.update_position(std::get<1>(*b.source_pile).back().img(), std::get<3>(*b.source_pile), true);
							continue;
						}

						std::get<1>(*b.destination_pile).push_front(std::move(std::get<1>(*b.source_pile).back()));
						std::get<1>(*b.source_pile).pop_back();

						std::get<1>(*b.destination_pile).back().position() = Card_State::face_up;

						std::get<0>(*b.source_pile) = false;
						std::get<0>(*b.destination_pile) = true;

						b.update_position(std::get<1>(*b.destination_pile).front().img(), std::get<3>(*b.destination_pile), true);

						++db.gs;

						db.gs(b.piles);
					}
				}

				else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
				{
					if (mouseButtonPressed->button == sf::Mouse::Button::Left)
					{
						auto cursor_pos = sf::Vector2f{ sf::Mouse::getPosition(window).x + .0f, sf::Mouse::getPosition(window).y + .0f };
						db.mp(window, cursor_pos);
						b(cursor_pos);
					}
				}
			}

			// clear the window with blue color
			window.clear(sf::Color{ 33,46,82 });

			//draw to window
			window.draw(db);

			enable_shader(b);

			window.draw(b);

			// end the current frame
			window.display();
		}
	}
private:
	sf::RenderWindow			 window{ sf::VideoMode({ 1000, 900 }), "Clock Solitaire", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed };
	sf::ContextSettings		     settings;
	sf::Shader						 glow_shader{ std::filesystem::path{Directory_Manager::assets_dir() / "shader/effect.frag"}, sf::Shader::Type::Fragment };
	sf::Image						 cursor_image{ std::filesystem::path{Directory_Manager::assets_dir() / "cursor/cursor_ice_white.png"} };
	std::optional<sf::Cursor> cursor = sf::Cursor::createFromPixels(cursor_image.getPixelsPtr(), sf::Vector2u{ 10,10 }, sf::Vector2u{ 0,0 });
	sf::RectangleShape			 glow_rect;
	bool shader_enabled{};
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