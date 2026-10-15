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
#include "../include/state.hpp"
#include "../include/util.hpp"

using namespace std::literals::string_literals;

struct Menu : public sf::Drawable
{
    static constexpr auto limit = 2;
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
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

    Game_State_Menu(General_Buttons& gb);

    auto operator()(const std::ranges::ref_view<std::deque<Card>> p, bool& app_state,
        sf::RenderWindow& rw, Board& b, sf::Clock& c) -> void;

    auto operator++() & -> const Game_State_Menu&;

    auto update_game_state(Button_Names::Game_State g_state, bool& app_state, sf::RenderWindow& rw
        , Board& b, sf::Clock& c) & ->void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Text move{ Util::load_font() };
    sf::Text game_id_t{ Util::load_font() };
    sf::Text game_state{ Util::load_font() };

    std::size_t game_id{};
    std::size_t move_count{};

    Button_Names::Game_State state{};

    Game_State_Button* gsbp{};
    std::vector<Game_State_Button> state_buttons;
};

struct Exit_Menu : public Menu
{
public:
    Exit_Menu(const General_Buttons& gb);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    Game_State_Button* gsbp{};
    std::vector<Game_State_Button> buttons;
};

template <typename T>
concept Is_Pointer = std::is_pointer_v<Game_State_Button*>;

template <typename T>
concept Is_Game_State_Button = std::same_as < T, std::span<Game_State_Button>>;

auto menu_click_listener(Is_Game_State_Button auto buttons, Is_Pointer auto& ptr, sf::Vector2f cursor_pos) -> void
{
    auto button = std::ranges::find_if(buttons, [&](const auto& b) {
        return std::get<0>(b.forms).getGlobalBounds().contains(cursor_pos);
        });

    if (button != std::end(buttons))
    {
        button->setting = ButtonMode::on;
        ptr = &(*button);
    }
};

auto menu_release_listener(Is_Pointer auto& ptr, sf::Vector2f cursor_pos,
    bool& app_state, sf::RenderWindow& rw, Board& b, sf::Clock& c, Game_State_Menu& gsm) -> void
{
    if (ptr)
    {
        if (std::get<0>(ptr->forms).getGlobalBounds().contains(cursor_pos))
        {
            gsm.update_game_state(ptr->name, app_state, rw, b, c);
        }

        ptr->setting = ButtonMode::off;
    }

    ptr = nullptr;
};

#endif //MENU_HPP