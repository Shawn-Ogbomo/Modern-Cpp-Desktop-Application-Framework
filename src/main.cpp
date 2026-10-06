#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <chrono>
#include <iostream>
#include <iterator>

#include "../include/board.hpp"
#include "../include/dash_board.hpp"
#include "../include/deck.hpp"
#include "../include/directory_manager.hpp"
#include "../include/menu.hpp"
#include "../include/music_player.hpp"
#include "../include/time_status.hpp"

class Application
{
public:
    Application()
    {
        if (!sf::Shader::isAvailable())
        {
            throw std::runtime_error{ "Shaders are not supported on this GPU...\n" };
        }

        static const auto dummyTexture = sf::Texture(sf::Vector2u(1, 1));

        const auto innerSize = sf::Vector2f(96, 144);

        const auto glowWidth = 10.f;

        const auto outerSize = sf::Vector2f{ innerSize + sf::Vector2f(glowWidth * 2, glowWidth * 2) };

        glow_rect.setSize(outerSize);

        glow_rect.setTexture(&dummyTexture); // Forces SFML to supply UV map coordinates

        const auto ratioX = innerSize.x / outerSize.x;
        const auto ratioY = innerSize.y / outerSize.y;

        glow_shader.setUniform("u_glowRatioX", ratioX);
        glow_shader.setUniform("u_glowRatioY", ratioY);

        const auto parchment_white = sf::Color{ 240, 245, 245 };

        glow_shader.setUniform("u_glowColor", sf::Glsl::Vec4(parchment_white.r / 255.f, parchment_white.g
            / 255.f, parchment_white.b / 255.f, parchment_white.a / 255.f));

        settings.antiAliasingLevel = 15;
        window.setMouseCursor(cursor.value());
        window.setIcon(sf::Image{ Directory_Manager::assets_dir() / "icon" / "7_diamonds_new.png" });
    }

    auto enable_shader(const Board& b) -> void
    {
        if (b.destination_pile != std::end(b.piles) && b.source_pile != std::end(b.piles)
            && std::get<2>(*b.destination_pile) == std::get<1>(*b.source_pile).back().value())
        {
            const auto pos = std::get<1>(*b.destination_pile).front().img().first.getPosition();
            glow_rect.setPosition(sf::Vector2f{ pos.x - 10, pos.y - 10 });
            window.draw(glow_rect, &glow_shader);
            shader_enabled = true;
            return;
        }

        shader_enabled = false;
    }

    auto run() -> void
    {
        auto sp_clock = std::make_shared<sf::Clock>();

        auto de = Deck{};

        auto b = std::make_shared<Board>(de);

        auto db = DashBoard{ sp_clock, b };

        // run the program as long as the window is open
        while (window.isOpen())
        {
            db.mp.idle();

            db.ts.update();

            // check all the window's events that were triggered since the last iteration of the loop
            while (const std::optional event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                {
                    window.close();
                }

                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                {
                    ///TODO: Give your Quit button the same value as sf::Keyboard::Scancode:Escape to exit on click.
                    ///TODO: Or do it in the click listener.
                    if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    {
                        window.close();
                    }
                }

                else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
                {
                    if (b->source_pile != std::end(b->piles))
                    {
                        b->update_position(std::get<1>(*b->source_pile).back().img(), sf::Vector2f{ mouseMoved->position.x
                            + .0f, mouseMoved->position.y + .0f });
                        b->operator()();
                    }
                }

                else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
                {
                    if (mouseButtonReleased->button == sf::Mouse::Button::Left)
                    {
                        const auto cursor_pos = sf::Vector2f{ sf::Mouse::getPosition(window).x
                            + .0f, sf::Mouse::getPosition(window).y + .0f };

                        db.mp.release_listener(cursor_pos);
                        db.gsm.release_listener(cursor_pos);

                        if (b->source_pile != std::end(b->piles))
                        {
                            if (!shader_enabled)
                            {
                                b->update_position(std::get<1>(*b->source_pile).back().img(), std::get<3>(*b->source_pile), true);
                                continue;
                            }

                            auto& src_cards = std::get<1>(*b->source_pile);
                            auto& dst_cards = std::get<1>(*b->destination_pile);

                            dst_cards.emplace_front(src_cards.back());
                            src_cards.pop_back();

                            dst_cards.back().position() = Card_State::face_up;

                            auto& src_pile_state = std::get<0>(*b->source_pile);
                            auto& dst_pile_state = std::get<0>(*b->destination_pile);

                            b->pos_prev = std::get<2>(*b->destination_pile);

                            src_pile_state = false;
                            dst_pile_state = true;

                            ++db.gsm;

                            db.gsm(std::get<1>(b->piles.back()));

                            b->update_position(dst_cards.front().img(), std::get<3>(*b->destination_pile), true);
                        }
                    }
                }

                else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                {
                    if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                    {
                        const auto cursor_pos = sf::Vector2f{ sf::Mouse::getPosition(window).x
                            + .0f, sf::Mouse::getPosition(window).y + .0f };

                        db.mp.click_listener(cursor_pos);
                        db.gsm.click_listener(cursor_pos);
                        b->operator()(cursor_pos);
                    }
                }
            }

            // clear the window with blue color
            window.clear({ 33, 46, 82 });

            // draw to window
            window.draw(db);

            enable_shader(*b);

            window.draw(*b);

            // end the current frame
            window.display();
        }
    }

private:
    sf::ContextSettings           settings;
    sf::RenderWindow           window{ sf::VideoMode({ 1000, 900 }), "Clock Solitaire", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed };
    sf::Shader                       glow_shader{ std::filesystem::path{ Directory_Manager::assets_dir() / "shader" / "effect.frag" }, sf::Shader::Type::Fragment };
    sf::Image                        cursor_image{ std::filesystem::path{ Directory_Manager::assets_dir() / "cursor" / "cursor_ice_white.png" } };
    std::optional<sf::Cursor> cursor = sf::Cursor::createFromPixels(cursor_image.getPixelsPtr(), sf::Vector2u{ 10, 10 }, sf::Vector2u{ 0, 0 });
    sf::RectangleShape          glow_rect;
    bool                               shader_enabled{};
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