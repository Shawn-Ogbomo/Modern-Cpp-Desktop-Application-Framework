#include <cmath>
#include <ranges>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <numbers>

#include "../include/util.hpp"
#include "../include/board.hpp"

namespace rng = std::ranges;
using namespace std::numbers;

auto::Board::update_position(std::pair<sf::Sprite&, sf::Sprite&> img, sf::Vector2f dest_pos, bool update_It_state) -> void
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

	if (const auto center = sf::Vector2f{ ((center_x * 2) - pos_card.x) / 2, ((center_y * 2) - pos_card.y) / 2 };
		rank == Rank_Lib::Rank::king)
	{
		front.setPosition(center);
		back.setPosition(center);
		return;
	}

	const auto a = sf::Angle{ sf::radians(v1 * 2.0f * pi / (v2 - 1.0f) - (pi / 2.0f)) };

	auto a_radians = a.asRadians();
	auto pos = sf::Vector2f{ center_x + radius * std::cos(a_radians) - (pos_card.x / 2.0f), center_y + (radius * std::sin(a_radians)) - pos_card.y / 2.0f };

	front.setPosition(pos);
	back.setPosition(pos);
}

Board::Board(Deck& d)
	:source_pile{ std::end(piles) },
	destination_pile(std::end(piles))
{
	for (auto index = 0; auto& pile : piles)
	{
		Util::allocate(pile);

		auto& [state, cards, rank, pos] = pile;
		rank = Rank_Lib::ranks[index];

		for (auto& card : cards)
		{
			card = d.draw();

			auto [face, reverse] = card.img();
			position_card(face, reverse, rank, index, total_piles);
		}

		pos = std::get<1>(pile).back().img().first.getPosition();

		++index;
	}

	auto& [state, cards, rank, pos] = piles.back();
	state = true;

	cards.back().position() = Card_State::face_up;
}

/// TODO: refractor this to update the src or destination pile within the operator and not by return...
 /// Why does src = found not work but source_pile = found does???
 /// Why does the function work without passing in any iterator and the instance b of source and destination are updated?
 /// Why does passing in iterators and assigning them to the returned iterator of found result in end iterator when returning from the function??
 /// The moving card triggers the shader on if it is ont touching any other cards if it has touched the correct pile.
auto Board::operator ()(sf::Vector2f pos)->void
{
	for (auto it = piles.begin(); it != piles.end(); ++it)
	{
		auto& [active, pile, rank, internal_pos] = *it;
		const auto& [face, reverse] = pile.front().img();

		if (active && face.getGlobalBounds().contains(pos))
		{
			source_pile = it;
			return;
		}

		if (source_pile != std::end(piles) && face.getGlobalBounds().findIntersection(std::get<1>(*source_pile).back().img().first.getGlobalBounds()))
		{
			destination_pile = it;
			return;
		}
	}

	destination_pile = std::end(piles);
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto pile_active = [](auto p) { return std::get<0>(p); };
	auto pile_inactive = [](auto internal_p) -> bool { return !(std::get<0>(internal_p)); };

	for (auto& pile : std::views::elements<1>(piles | std::views::filter(pile_inactive)))
	{
		for (const auto& card : pile)
		{
			target.draw(card);
		}
	}

	for (auto& pile : std::views::elements<1>(piles | std::views::filter(pile_active)))
	{
		for (const auto& card : pile)
		{
			target.draw(card);
		}
	}
}