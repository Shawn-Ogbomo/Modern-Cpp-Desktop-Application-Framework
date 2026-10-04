#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <functional>
#include <ranges>
#include <string>
#include <vector>

#include"../include/board.hpp"
#include "../include/button.hpp"
#include "../include/directory_manager.hpp"
#include "../include/random_number_gen.hpp"
#include "../include/state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

class Game_State_Button;

using namespace std::literals::string_literals;

struct Menu : public sf::Drawable
{
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual void click_listener(sf::Vector2f cursor_pos) & = 0;
    virtual void release_listener(sf::Vector2f cursor_pos) & = 0;
    virtual ~Menu() = default;
};

class Game_State_Menu : public Menu
{
public:
    Game_State_Menu();
    auto operator()(const std::ranges::ref_view<std::deque<Card>> p) -> void;
    auto operator()(Game_State gs) & -> void;
    auto operator++() & -> const Game_State_Menu&;

    auto click_listener(sf::Vector2f cursor_pos) & ->void;
    auto release_listener(sf::Vector2f cursor_pos) & ->void;
    auto status() const& -> const Game_State& { return state; };
    auto set_clock(std::shared_ptr<sf::Clock> shptr_c) & ->void { c_sp = shptr_c; }
    auto set_board(std::shared_ptr<Board> shptr_b) & -> void { b_sp = shptr_b; }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    struct  Update_Game_State
    {
        auto operator()(Game_State_Menu& gsm, Game_State g_state) -> void;
    };

    struct Lose_Condition
    {
        auto operator()(const Card& card)const ->bool;
    };

    struct State_Label
    {
        std::array <std::string, 4> states{
            "State"s.append(16, ' ') + ": " + "Playing",
            "State"s.append(16, ' ') + ": " + "Paused",
            "State"s.append(16, ' ') + ": " + "Win",
            "State"s.append(16, ' ') + ": " + "Lose"
        };
    };

    auto get_labels() & -> const State_Label&
    {
        static const auto labels = State_Label{};
        return labels;
    }

    auto set_pile_state() & ->void;

    sf::Text move{ Util::load_font() };
    sf::Text game_id_t{ Util::load_font() };
    sf::Text game_state{ Util::load_font() };

    std::size_t game_id{};
    std::size_t move_count{};

    Game_State state{};

    std::shared_ptr<sf::Clock> c_sp;
    std::shared_ptr<Board> b_sp;

    General_Buttons gb_interface;
    std::vector<Game_State_Button> state_buttons;
};

#endif //MENU_HPP