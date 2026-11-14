#ifndef BOARD_HPP
#define BOARD_HPP

#include <array>
#include <deque>
#include <utility>

#include "../include/deck.hpp"

struct Pile
{
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
public:
    explicit Board(Deck& d);
    operator bool() const { return static_cast<bool>(mode); }
    auto operator = (Board&&)
        -> Board & = delete;
    auto operator()(sf::Vector2f pos = {}) -> void;

    auto state() & ->ButtonMode& { return mode; }
    auto active_pile() -> Rank_Lib::Rank& { return pos_prev; }
    auto active_pile() const -> const Rank_Lib::Rank& { return pos_prev; }

    auto source_pile() -> std::span<Pile>& { return internal_source_pile; }
    auto destination_pile() -> std::span<Pile>& { return internal_destination_pile; }
    auto source_pile() const -> const std::span<const Pile> { return internal_source_pile; }
    auto destination_pile() const -> const std::span<const Pile> { return internal_destination_pile; }

    auto piles() & -> Piles& { return internal_piles; }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    Piles internal_piles{};
    ButtonMode mode{};
    Rank_Lib::Rank pos_prev{};
    std::span<Pile> internal_source_pile;
    std::span<Pile> internal_destination_pile;
};

auto move_card(sf::Sprite& card_img_f, sf::Sprite& card_img_b
    , sf::Vector2f dest_pos, std::span<Pile>& src_p, std::span<Pile>& dst_p,
    bool update_It_state = false)
    -> void;

#endif // BOARD_HPP