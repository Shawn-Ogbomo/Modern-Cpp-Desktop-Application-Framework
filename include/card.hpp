#ifndef CARD_HPP
#define CARD_HPP

#include <SFML/Graphics.hpp>

#include <utility>

#include "../include/rank.hpp"
#include "../include/state.hpp"
#include "../include/suit.hpp"
#include "../include/texture_manager.hpp"

struct Card : public sf::Drawable
{
    Card() = default;
    explicit Card(std::string_view card_name, const sf::Texture& f
        , const sf::Texture& re
        , Card_State st = Card_State::face_down);

    virtual void draw(sf::RenderTarget& target
        , sf::RenderStates states) const;
    
    Suit suit{};
    Card_State state{};
    Rank_Lib::Rank rank{};
    sf::Sprite face{ default_texture() };
    sf::Sprite reverse{ default_texture() };
};

#endif // CARD_HPP