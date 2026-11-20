#ifndef CARD_HPP
#define CARD_HPP

#include <SFML/Graphics.hpp>

#include <utility>

#include "../include/rank.hpp"
#include "../include/state.hpp"
#include "../include/suit.hpp"
#include "../include/texture_manager.hpp"

class Card : public sf::Drawable
{
public:
    Card() = default;
    explicit Card(std::string_view card_name, const sf::Texture& f
        , const sf::Texture& re
        , Card_State st = Card_State::face_down);

    auto rank() const& ->Rank_Lib::Rank { return internal_rank; }

    auto state() const& -> const Card_State& { return internal_state; }
    auto state() & ->Card_State& { return internal_state; }

    auto face() const& ->const sf::Sprite& { return internal_face; }
    auto face() & ->sf::Sprite& { return internal_face; }

    auto reverse() const& -> const sf::Sprite& { return internal_reverse; }
    auto reverse() & ->sf::Sprite& { return internal_reverse; }

    virtual void draw(sf::RenderTarget& target
        , sf::RenderStates states) const;
private:
    Suit suit{};
    Card_State internal_state{};
    Rank_Lib::Rank internal_rank{};
    sf::Sprite internal_face{ default_texture() };
    sf::Sprite internal_reverse{ default_texture() };
};

#endif // CARD_HPP