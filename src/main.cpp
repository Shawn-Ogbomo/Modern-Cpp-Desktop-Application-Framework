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
#include "../include/component_manager.hpp"
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
        if (!b.destination_pile().empty() && !b.source_pile().empty()
            && b.destination_pile().front().rank == b.source_pile().front().cards.back().rank())
        {
            const auto pos = b.destination_pile().front().cards.front().face().getPosition();
            glow_rect.setPosition(sf::Vector2f{ pos.x - 10, pos.y - 10 });
            window.draw(glow_rect, &glow_shader);
            shader_enabled = true;
            return;
        }

        shader_enabled = false;
    }

    auto run() -> void
    {
        Database_Manager db;
        auto tm = Texture_Manager{};
        auto mp = Music_Player{ tm.media_buttons() };

        while (running)
        {
            auto clock = sf::Clock{};
            auto de = Deck{ tm.cards() };
            auto b = Board{ de };
            auto ts = Time_Status{};

            auto em = Exit_Menu{ tm.general_buttons() };
            auto gsm = Game_State_Menu{ tm.general_buttons() };
            auto cm = Confirmation_Menu{ tm.general_buttons(),tm.text_boxes(), window };
            auto im = Input_Menu{ tm.general_buttons(),tm.text_boxes(), window };

            auto c_m = Component_Manager{ { &running,1 },{ &b,1 },{ &clock,1 },{ &em,1 }
           ,{ &mp,1 },{ &window,1 },{ &gsm,1 },{ &cm,1 },{ &im,1 } };

            auto v1 = std::variant<std::span<GSB>, std::span<EMB>
                , std::span<CMB>, std::span<MB >, std::span<IMB>>{};

            auto o1 = overload
            {
                [&, this](std::span<GSB>) { gsm.update_game_state(gsm.clicked_button()
                    .front().contents.name, c_m); }

                    ,[&, this](std::span<EMB>) {em.state_manager(c_m);  }

                        ///TODO: Remove update game_State statement from CMB visitor.
                        ,[&, this](std::span<CMB>) { cm.state_manager(c_m); /*gsm.update_game_state(gsm.status(),c_m);*/ }

                        ,[&, this](std::span<MB>) { mp.operator()(mp.clicked_button()
                            .front().contents.name); }

                         ,[&, this](std::span<IMB>) { im.state_manager(c_m); }
            };

            const auto& component_click_listener = [&](auto& component, auto& buttons, auto& spn
                , sf::Vector2f cursor_pos) -> void
                {
                    auto button = std::ranges::find_if(buttons, [&](const auto& b) {
                        return(component && b.forms.form_1.getGlobalBounds()
                            .contains(cursor_pos));
                        });

                    if (button != std::end(buttons))
                    {
                        button->contents.setting = ButtonMode::on;
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
                        if (component && spn.front().forms.form_1.getGlobalBounds()
                            .contains(cursor_pos))
                        {
                            std::visit(o1, v1);
                        }

                        spn.front().contents.setting = ButtonMode::off;
                    }

                    spn = std::span<spn_type>{};
                };

            // run the program as long as the window is open
            gsm.update_game_state(B_N::Game_State::win, c_m);
            while (window.isOpen())
            {
                if (em.restart())
                {
                    break;
                }

                mp.idle();

                im.text_box().field().caret().idle();

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

                        constexpr auto a = sf::Keyboard::Scancode::A;
                        constexpr auto z = sf::Keyboard::Scancode::Z;

                        if (const auto input_menu_active = im.operator bool())
                        {
                            if (keyPressed->scancode >= a && keyPressed->scancode <= z)
                            {
                                im.text_box().field().operator+=(keyPressed->scancode);
                            }

                            else if (keyPressed->scancode >= sf::Keyboard::Scancode::Backspace)
                            {
                                im.text_box().field().operator-=(keyPressed->scancode);
                            }
                        }
                    }

                    else if (const auto* keyRelease = event->getIf<sf::Event::KeyReleased>())
                    {
                        ///TODO: Return the caret to idle state
                    }

                    else if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
                    {
                        if (!b.source_pile().empty())
                        {
                            move_card(b.source_pile().front().cards.back().face()
                                , b.source_pile().front().cards.back().reverse(), sf::Vector2f{ mouseMoved->position.x
                               + .0f, mouseMoved->position.y + .0f }, b.source_pile(), b.destination_pile());

                            b.operator()();
                        }
                    }

                    else if (const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>())
                    {
                        if (mouseButtonReleased->button == sf::Mouse::Button::Left)
                        {
                            const auto cursor_pos = sf::Vector2f{ sf::Mouse::getPosition(window).x
                                + .0f, sf::Mouse::getPosition(window).y + .0f };

                            component_release_listener(mp, mp.clicked_button(), cursor_pos);
                            component_release_listener(gsm, gsm.clicked_button(), cursor_pos);
                            component_release_listener(em, em.clicked_button(), cursor_pos);
                            component_release_listener(cm, cm.clicked_button(), cursor_pos);
                            component_release_listener(im, im.clicked_button(), cursor_pos);

                            if (!b.source_pile().empty())
                            {
                                if (!shader_enabled)
                                {
                                    move_card(b.source_pile().front().cards.back().face()
                                        , b.source_pile().front().cards.back().reverse(),
                                        b.source_pile().front().location, b.source_pile(), b.destination_pile(), true);

                                    continue;
                                }

                                auto& src_cards = b.source_pile().front().cards;
                                auto& dst_cards = b.destination_pile().front().cards;

                                dst_cards.emplace_front(src_cards.back());
                                src_cards.pop_back();

                                dst_cards.back().state() = Card_State::face_up;

                                auto& src_pile_state = b.source_pile().front().active;
                                auto& dst_pile_state = b.destination_pile().front().active;

                                b.active_pile() = b.destination_pile().front().rank;

                                src_pile_state = false;
                                dst_pile_state = true;

                                ++gsm;

                                gsm(b.piles().back().cards, c_m);

                                move_card(dst_cards.front().face()
                                    , dst_cards.front().reverse(),
                                    b.destination_pile().front().location, b.source_pile(), b.destination_pile(), true);
                            }
                        }
                    }

                    else if (const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>())
                    {
                        if (mouseButtonPressed->button == sf::Mouse::Button::Left)
                        {
                            const auto cursor_pos = sf::Vector2f{ sf::Mouse::getPosition(window).x
                                + .0f, sf::Mouse::getPosition(window).y + .0f };

                            component_click_listener(mp, mp.buttons(), mp.clicked_button(), cursor_pos);
                            component_click_listener(em, em.buttons(), em.clicked_button(), cursor_pos);
                            component_click_listener(gsm, gsm.buttons(), gsm.clicked_button(), cursor_pos);
                            component_click_listener(cm, cm.buttons(), cm.clicked_button(), cursor_pos);
                            component_click_listener(im, im.buttons(), im.clicked_button(), cursor_pos);
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
                window.draw(im);

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