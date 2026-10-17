#ifndef CARD_HPP
#define CARD_HPP

#include <SFML/Graphics.hpp>

#include <functional>
#include <span>
#include <utility>

#include "../include/rank.hpp"
#include "../include/state.hpp"
#include "../include/suit.hpp"
#include "../include/texture_manager.hpp"

class Card : public sf::Drawable
{
public:
    Card() = default;
    explicit Card(std::string_view card_name, std::span<const sf::Texture> f, std::span<const sf::Texture>re
        , Card_State st = Card_State::face_down);

    auto position() & -> std::span<Card_State> { return { &state, 1 }; }
    auto position()const& -> std::span<const Card_State> { return { &state,1 }; }
    auto value() const& -> std::span<const Rank_Lib::Rank> { return { &rank, 1 }; }
    auto img() & -> std::pair<sf::Sprite&, sf::Sprite&> { return { std::ref(face),std::ref(reverse) }; }
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        state == Card_State::face_up ? target.draw(face) : target.draw(reverse);
    }

    Suit suit{};
    Card_State state{};
    Rank_Lib::Rank rank{};
    sf::Sprite face{ default_texture() };
    sf::Sprite reverse{ default_texture() };
};

#endif // CARD_HPP