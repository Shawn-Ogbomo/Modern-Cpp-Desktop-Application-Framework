#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <chrono>
#include <iostream>
#include <iterator>
#include <variant>

#include "../include/board.hpp"
#include "../include/deck.hpp"
#include "../include/directory_manager.hpp"
#include "../include/menu.hpp"
#include "../include/music_player.hpp"
#include "../include/refs.hpp"
#include "../include/time_status.hpp"

namespace B_N = Button_Names;

template<typename... Ts>
struct overload : Ts...{using Ts::operator()...; };

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
            && (*b.destination_pile).rank == (*b.source_pile).cards.back().value().front())
        {
            const auto pos = (*b.destination_pile).cards.front().img().first.getPosition();
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

            const auto gb = General_Buttons{};
            const auto tbs = Text_Boxes{};

            auto ts = Time_Status{ };
            static auto mp = Music_Player{};

            auto em = Exit_Menu{ gb };
            auto gsm = Game_State_Menu{ gb };
            auto cm = Confirmation_Menu{ gb,tbs,{ &window,1} };

            auto rc = Refs_Components{ {&running,1},{&b,1},{&clock,1},{&em,1}
           ,{&mp,1 },{&window,1},{&gsm,1},{&cm,1} };

            auto v1 = std::variant<std::span<Game_State_Button>, std::span<Exit_Menu_Button>
                , std::span<Confirmation_Button>, std::span<Media_Button>>{};

            auto o1 = overload
            {
                [&](std::span<Game_State_Button>) { gsm.update_game_state(gsm.gsbs.front().name, rc); },
                [&](std::span<Exit_Menu_Button>) {gsm.update_game_state(em.embs.front().name, rc);  },
                [&](std::span<Confirmation_Button>) { cm.state_manager(rc); },
                [&](std::span<Media_Button>) { mp.operator()(mp.mbs.front().name); }
            , };

            const auto& component_click_listener = [&](auto buttons, auto& spn, sf::Vector2f cursor_pos) -> void
                {
                    auto button = std::ranges::find_if(buttons, [&](const auto& b) {
                        return(b.forms.form_1).getGlobalBounds().contains(cursor_pos);
                        });

                    if (button != std::end(buttons))
                    {
                        button->setting = ButtonMode::on;
                        spn = { &(*button) ,1 };
                        v1 = spn;
                    }
                };

            const auto& component_release_listener = [&](auto& component, auto& spn,
                sf::Vector2f cursor_pos) -> void
                {
                    using spn_type = std::remove_cvref_t<decltype(spn)>::element_type;

                    if (!spn.empty())
                    {
                        if (component && spn.front().forms.form_1.getGlobalBounds().contains(cursor_pos))
                        {
                            std::visit(o1, v1);
                        }

                        spn.front().setting = ButtonMode::off;
                    }

                    spn = std::span<spn_type>{};
                };

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
                            b.update_position((*b.source_pile).cards.back().img(), sf::Vector2f{ mouseMoved->position.x
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

                            component_release_listener(mp, mp.mbs, cursor_pos);
                            component_release_listener(gsm, gsm.gsbs, cursor_pos);
                            component_release_listener(em, em.embs, cursor_pos);
                            component_release_listener(cm, cm.cbs, cursor_pos);

                            if (b.source_pile != std::end(b.piles))
                            {
                                if (!shader_enabled)
                                {
                                    b.update_position((*b.source_pile).cards.back().img()
                                        , (*b.source_pile).location, true);

                                    continue;
                                }

                                auto& src_cards = (*b.source_pile).cards;
                                auto& dst_cards = (*b.destination_pile).cards;

                                dst_cards.emplace_front(src_cards.back());
                                src_cards.pop_back();

                                dst_cards.back().position().front() = Card_State::face_up;

                                auto& src_pile_state = (*b.source_pile).active;
                                auto& dst_pile_state = (*b.destination_pile).active;

                                b.pos_prev = (*b.destination_pile).rank;

                                src_pile_state = false;
                                dst_pile_state = true;

                                ++gsm;

                                gsm(b.piles.back().cards, rc);

                                b.update_position(dst_cards.front().img(), (*b.destination_pile).location, true);
                            }
                        }
                    }

                    else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                    {
                        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                        {
                            const auto cursor_pos = sf::Vector2f{ sf::Mouse::getPosition(window).x
                                + .0f, sf::Mouse::getPosition(window).y + .0f };

                            component_click_listener(std::span{ mp.buttons }, mp.mbs, cursor_pos);
                            component_click_listener(std::span{ em.buttons }, em.embs, cursor_pos);
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