#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <chrono>
#include <iostream>
#include <iterator>

#include "../include/board.hpp"
#include "../include/component_handler.hpp"
#include "../include/deck.hpp"
#include "../include/directory_manager.hpp"
#include "../include/menu.hpp"
#include "../include/music_player.hpp"
#include "../include/refs.hpp"
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
            && std::get<2>(*b.destination_pile) == std::get<1>(*b.source_pile).back().value().front())
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
        while (running)
        {
            auto clock = sf::Clock{};
            auto de = Deck{};
            auto b = Board{ de };

            auto gb = General_Buttons{};
            auto tbs = Text_Boxes{};

            auto ts = Time_Status{ };
            static auto mp = Music_Player{};

            auto em = Exit_Menu{ gb };
            auto gsm = Game_State_Menu{ gb };
            auto cm = Confirmation_Menu{ gb,tbs };

            auto rc = Refs_Components{ {&running,1},{&b,1},{&clock,1},{&em,1}
           ,{&mp,1 },{&window,1},{&gsm,1},{&cm,1} };

            // run the program as long as the window is open
            while (window.isOpen())
            {
                if (gsm.state == Button_Names::Game_State::restart)
                {
                    break;
                }

                mp.idle();

                ts.update(clock);

                // check all the window's events that were triggered since the last iteration of the loop
                while (const std::optional event = window.pollEvent())
                {
                    if (event->is<sf::Event::Closed>())
                    {
                        running = false;
                        window.close();
                    }

                    if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                    {
                        if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                        {
                            running = false;
                            window.close();
                        }
                    }

                    else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
                    {
                        if (b.source_pile != std::end(b.piles))
                        {
                            b.update_position(std::get<1>(*b.source_pile).back().img(), sf::Vector2f{ mouseMoved->position.x
                                + .0f, mouseMoved->position.y + .0f });
                            b.operator()();
                        }
                    }

                    else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
                    {
                        if (mouseButtonReleased->button == sf::Mouse::Button::Left)
                        {
                            const auto cursor_pos = sf::Vector2f{ sf::Mouse::getPosition(window).x
                                + .0f, sf::Mouse::getPosition(window).y + .0f };

                            mp.release_listener(cursor_pos);
                            component_release_listener(em, rc, em.gsbs, cursor_pos);
                            component_release_listener(gsm, rc, gsm.gsbs, cursor_pos);
                            cm.release_listener(rc, cm.cbs, cursor_pos);

                            if (b.source_pile != std::end(b.piles))
                            {
                                if (!shader_enabled)
                                {
                                    b.update_position(std::get<1>(*b.source_pile).back().img()
                                        , std::get<3>(*b.source_pile), true);

                                    continue;
                                }

                                auto& src_cards = std::get<1>(*b.source_pile);
                                auto& dst_cards = std::get<1>(*b.destination_pile);

                                dst_cards.emplace_front(src_cards.back());
                                src_cards.pop_back();

                                dst_cards.back().position().front() = Card_State::face_up;

                                auto& src_pile_state = std::get<0>(*b.source_pile);
                                auto& dst_pile_state = std::get<0>(*b.destination_pile);

                                b.pos_prev = std::get<2>(*b.destination_pile);

                                src_pile_state = false;
                                dst_pile_state = true;

                                ++gsm;

                                gsm(std::get<1>(b.piles.back()), rc);

                                b.update_position(dst_cards.front().img(), std::get<3>(*b.destination_pile), true);
                            }
                        }
                    }

                    else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                    {
                        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                        {
                            const auto cursor_pos = sf::Vector2f{ sf::Mouse::getPosition(window).x
                                + .0f, sf::Mouse::getPosition(window).y + .0f };

                            component_click_listener(std::span{mp.buttons}, mp.mbs, cursor_pos);
                            component_click_listener(std::span{ em.buttons }, em.gsbs, cursor_pos);
                            component_click_listener(std::span{ gsm.state_buttons }, gsm.gsbs, cursor_pos);
                            component_click_listener(std::span{ cm.buttons }, cm.cbs, cursor_pos);
                            b.operator()(cursor_pos);
                        }
                    }
                }

                // clear the window with blue color
                window.clear({ 33, 46, 82 });

                // draw to window

                enable_shader(b);

                window.draw(gsm);
                window.draw(ts);
                window.draw(mp);
                window.draw(em);

                window.draw(b);
                window.draw(cm);

                // end the current frame
                window.display();
            }
        }
    }
private:
    sf::ContextSettings           settings;
    sf::RenderWindow           window{ sf::VideoMode({ 1000, 900 }), "Clock Solitaire", sf::Style::Titlebar | sf::Style::Close, sf::State::Windowed };
    sf::Shader                       glow_shader{ std::filesystem::path{ Directory_Manager::assets_dir() / "shader" / "effect.frag" }, sf::Shader::Type::Fragment };
    sf::Image                        cursor_image{ std::filesystem::path{ Directory_Manager::assets_dir() / "cursor" / "cursor_ice_white.png" } };
    std::optional<sf::Cursor> cursor{ sf::Cursor::createFromPixels(cursor_image.getPixelsPtr(), sf::Vector2u{ 10, 10 }, sf::Vector2u{ 0, 0 }) };
    sf::RectangleShape          glow_rect;
    bool                               shader_enabled{};
    bool                               running{ true };
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