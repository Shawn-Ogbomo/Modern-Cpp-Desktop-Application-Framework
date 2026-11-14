#include <cmath>
#include <numbers>
#include <ranges>

#include "../include/board.hpp"
#include "../include/util.hpp"

using namespace std::numbers;
namespace rng = std::ranges;

auto move_card(sf::Sprite& card_img_f, sf::Sprite& card_img_b, sf::Vector2f dest_pos
    , std::span<Pile>& src_p, std::span<Pile>& dst_p, bool update_It_state) -> void
{
    card_img_f.setPosition(dest_pos);
    card_img_b.setPosition(dest_pos);

    if (update_It_state)
    {
        src_p = std::span<Pile>{};
        dst_p = std::span<Pile>{};
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

Board::Board(Deck& d) : pos_prev{ Rank_Lib::ranks.back() }, mode{ ButtonMode::on }
{
    for (auto index = 0; auto& pile : internal_piles)
    {
        Util::allocate(pile);

        auto& [pile_active, cards, rank, pos] = pile;
        rank = Rank_Lib::ranks[index];

        for (auto& card : cards)
        {
            card = d.draw();

            position_card(card.face, card.reverse
                , rank, index, total_piles);
        }

        pos = cards.back().face.getPosition();

        ++index;
    }

    auto& [pile_active, cards, rank, pos] = internal_piles.back();
    pile_active = true;

    cards.back().state = Card_State::face_up;
}

auto Board::operator()(sf::Vector2f pos) -> void
{
    ///TODO: Work on removing this and getting it into the universal click and release listener.
    if (mode == ButtonMode::on)
    {
        for (auto& stack : internal_piles) [[likely]]
        {
            auto& [pile_active, pile, rank, internal_pos] = stack;
            const auto& face = pile.front().face;

            if (pile_active && face.getGlobalBounds().contains(pos))
            {
                internal_source_pile = { &stack,1 };
                return;
            }

            if (!internal_source_pile.empty() && face.getGlobalBounds().findIntersection(
                (internal_source_pile).front().cards.back().face.getGlobalBounds()))
            {
                internal_destination_pile = { &stack, 1 };
                return;
            }
        }

        internal_destination_pile = std::span<Pile>{};
    }
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    const auto& inactive = [&, this](const auto& p) -> bool { return !(p.active); };

    for (auto& stack : internal_piles | rng::views::filter(inactive))
    {
        for (const auto& card : stack.cards)
        {
            target.draw(card);
        }
    }

    for (const auto& card : (internal_piles[static_cast<int>(active_pile())].cards))
    {
        target.draw(card);
    }
}