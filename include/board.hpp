#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <deque>
#include <utility>

#include "../include/deck.hpp"

struct Pile
{
public:
    bool active{};
    std::deque<Card> cards;
    Rank_Lib::Rank rank{};
    sf::Vector2f location;
};

struct Board : public sf::Drawable
{
    static constexpr auto cards_pile = 4;
    static constexpr auto total_piles = 13;

    using Piles = std::array<Pile, total_piles>;
    using Pile_It = std::array<Pile, Board::total_piles>::iterator;
public:
    Board() = delete;
    explicit Board(Deck& d);
    auto operator()(sf::Vector2f pos = {}) -> void;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    auto update_position(std::pair<sf::Sprite&, sf::Sprite&> img,
        sf::Vector2f dest_pos, bool update_It_state = false)
        & -> void;

    Rank_Lib::Rank pos_prev{};

    Pile_It source_pile;
    Pile_It destination_pile;
    Piles piles{};
};

#endif // BOARD_HPP