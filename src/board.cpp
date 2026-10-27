#include <algorithm>
#include <cmath>
#include <iterator>
#include <numbers>

#include "../include/board.hpp"
#include "../include/util.hpp"

using namespace std::numbers;

auto Board::update_position(std::pair<sf::Sprite&, sf::Sprite&> img, sf::Vector2f dest_pos
    , bool update_It_state) & -> void
{
    auto& [face, reverse] = img;

    face.setPosition(dest_pos);
    reverse.setPosition(dest_pos);

    if (update_It_state)
    {
        source_pile = std::end(piles);
        destination_pile = std::end(piles);
    }
}

auto position_card(sf::Sprite& front, sf::Sprite& back, Rank_Lib::Rank rank, int v1, int v2) -> void
{
    const auto center_x = 500.0f;
    const auto center_y = 385.0f;
    const auto radius = 300.0f;
    const auto pos_card = front.getLocalBounds().size;

    if (const auto center = sf::Vector2f{ ((center_x * 2) - pos_card.x) / 2, ((center_y * 2)
        - pos_card.y) / 2 }; rank == Rank_Lib::Rank::king)
    {
        front.setPosition(center);
        back.setPosition(center);
        return;
    }

    const auto a = sf::radians(static_cast<float>(v1 * 2.0f * pi / (v2 - 1.0f) - (pi / 2.0f)));

    auto a_radians = a.asRadians();
    auto pos = sf::Vector2f{ center_x + radius * std::cos(a_radians) - (pos_card.x / 2.0f), center_y
        + (radius * std::sin(a_radians)) - pos_card.y / 2.0f };

    front.setPosition(pos);
    back.setPosition(pos);
}

Board::Board(Deck& d) : source_pile{ std::end(piles) }, destination_pile{ std::end(piles) }
, pos_prev{ Rank_Lib::ranks.back() }
{
    for (auto index = 0; auto& pile : piles) [[likely]]
    {
        Util::allocate(pile);

        auto& [pile_active, cards, rank, pos] = pile;
        rank = Rank_Lib::ranks[index];

        for (auto& card : cards)
        {
            card = d.draw();

            auto [face, reverse] = card.img();
            position_card(face, reverse, rank, index, total_piles);
        }

        pos = cards.back().img().first.getPosition();

        ++index;
    }

    auto& [pile_active, cards, rank, pos] = piles.back();
    pile_active = true;

    cards.back().position().front() = Card_State::face_up;
}

auto Board::operator()(sf::Vector2f pos) -> void
{
    for (auto it = piles.begin(); it != piles.end(); ++it) [[likely]]
    {
        auto& [pile_active, pile, rank, internal_pos] = *it;
        const auto& [face, reverse] = pile.front().img();

        if (pile_active && face.getGlobalBounds().contains(pos))
        {
            source_pile = it;
            return;
        }

        if (source_pile != std::end(piles) && face.getGlobalBounds().findIntersection(
            (*source_pile).cards.back().img().first.getGlobalBounds()))
        {
            destination_pile = it;
            return;
        }
    }

    destination_pile = std::end(piles);
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (auto i = 0, pos = 0; i < total_piles; ++i) [[likely]]
    {
        if (!(piles[i].active))
        {
            for (const auto& card : piles[i].cards)
            {
                target.draw(card);
            }
        }

        else if ((piles[i]).active)
        {
            pos = i;
        }

        if (piles[i].rank == Rank_Lib::Rank::king)
        {
            for (const auto& card : (piles[pos].cards))
            {
                target.draw(card);
            }
        }
    }
}