#ifndef GAME_STATUS_HPP
#define GAME_STATUS_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include <ranges>

#include"../include/board.hpp"
#include "../include/directory_manager.hpp"
#include "../include/random_number_gen.hpp"
#include "../include/state.hpp"
#include "../include/util.hpp"

class Game_Status : public sf::Drawable
{
public:
    Game_Status();
    auto operator()(const std::ranges::ref_view<std::deque<Card>> p, bool& pile_state) -> void;
    auto operator++() & -> const Game_Status&;

    auto status() const& -> const Game_State& { return state; };
private:
    struct Update_Game_State
    {
        auto operator()(Game_Status& gs, Game_State g_state, bool& pile_state) ->void;
    };

    struct Lose_Condition
    {
        auto operator()(const Card& card)const ->bool;
    };

    auto update() & -> void;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Text move{ Util::load_font() };
    sf::Text game_id_t{ Util::load_font() };
    sf::Text game_state{ Util::load_font() };

    std::size_t game_id{};
    std::size_t move_count{};
    Game_State state{};
};

#endif // GAME_STATUS_HPP