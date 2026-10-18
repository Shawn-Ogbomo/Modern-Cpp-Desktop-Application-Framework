#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <ranges>
#include <string>
#include <vector>

#include"../include/board.hpp"
#include "../include/button.hpp"
#include "../include/directory_manager.hpp"
#include "../include/random_number_gen.hpp"
#include "../include/refs.hpp"
#include "../include/state.hpp"
#include "../include/util.hpp"

using namespace std::literals::string_literals;

struct Menu : public sf::Drawable
{
    static constexpr auto limit = 2;
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual operator bool() const = 0;
    virtual ~Menu() = default;
};

struct Game_State_Button;
struct Exit_Menu_Button;

template<typename T>
concept Is_Valid_Menu = std::derived_from<T, Menu>;

struct Game_State_Menu : public Menu
{
public:
    struct Lose_Condition
    {
        auto operator()(const Card& card)const ->bool;
    };

    struct State_Label
    {
        std::array <std::string, 6> states{
            "State"s.append(16, ' ') + ": " + "Paused",
            "State"s.append(16, ' ') + ": " + "Playing",
            "State"s.append(16, ' ') + ": " + "Win",
            "State"s.append(16, ' ') + ": " + "Lose",
            "State"s.append(16, ' ') + ": " + "Restart",
            "State"s.append(16, ' ') + ": " + "Quit"
        };
    };

    auto get_labels() & -> const State_Label&
    {
        static const auto labels = State_Label{};
        return labels;
    }

    Game_State_Menu(const General_Buttons& gb);

    auto operator()(const std::ranges::ref_view<std::deque<Card>> p, Refs_Components& r_c) -> void;

    auto operator++() & -> const Game_State_Menu&;

    operator bool() const override { return static_cast<bool>(mode); }

    auto update_game_state(Button_Names::Game_State g_state, Refs_Components& r_c) & ->void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Text move{ Util::load_font() };
    sf::Text game_id_t{ Util::load_font() };
    sf::Text game_state{ Util::load_font() };

    std::size_t game_id{};
    std::size_t move_count{};

    Button_Names::Game_State state{};
    std::span<Game_State_Button> gsbs{};
    std::vector<Game_State_Button> state_buttons;

    ButtonMode mode{ ButtonMode::on };
};

struct Exit_Menu : public Menu
{
public:
    Exit_Menu(const General_Buttons& gb);
    operator bool() const override { return static_cast<bool>(mode); }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::span<Game_State_Button> gsbs;
    std::vector<Game_State_Button> buttons;

    ButtonMode mode{ ButtonMode::on };
};

template <typename T>
concept Is_Menu = std::is_pointer_v<Menu*>;

template <typename T>
concept Is_GS_Button = std::same_as < T, std::span<Game_State_Button>>;

auto menu_click_listener(Is_GS_Button auto buttons, auto& spn, sf::Vector2f cursor_pos) -> void
{
    auto button = std::ranges::find_if(buttons, [&](const auto& b) {
        return std::get<0>(b.forms).getGlobalBounds().contains(cursor_pos);
        });

    if (button != std::end(buttons))
    {
        button->setting = ButtonMode::on;
        spn = { &(*button) ,1 };
    }
};

auto menu_release_listener(const Is_Menu auto& menu, Refs_Components& r_c, auto& spn
    , sf::Vector2f cursor_pos) -> void
{
    if (!spn.empty())
    {
        if (menu && std::get<0>(spn.front().forms).getGlobalBounds().contains(cursor_pos))
        {
            r_c.sp7_gsm.front().update_game_state(spn.front().name, r_c);
        }

        spn.front().setting = ButtonMode::off;
    }

    spn = std::span<Game_State_Button>{};
};

#endif //MENU_HPP