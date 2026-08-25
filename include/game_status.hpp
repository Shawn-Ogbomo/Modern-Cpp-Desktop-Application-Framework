#ifndef GAME_STATUS_HPP
#define GAME_STATUS_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include"../include/board.hpp"
#include "../include/random_number_gen.hpp"
#include "../include/state.hpp"

class Game_Status : public sf::Drawable
{
    sf::Font font;

public:
    Game_Status();
    auto operator()(const std::deque<Card>& p, bool& pile_state) -> void;
    auto operator++() -> const Game_Status&;

private:
    struct Update_Game_State
    {
        auto operator()(Game_Status& gs, Game_State g_state, bool& pile_state) ->void;
    };

    struct Lose_Condition
    {
        auto operator()(Card card)const ->bool;
    };

    auto update() -> void;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Text move{ font };
    sf::Text game_id_t{ font };
    sf::Text game_state{ font };

    std::size_t game_id{};
    std::size_t move_count{};
    Game_State state{};
};

#endif // GAME_STATUS_HPP