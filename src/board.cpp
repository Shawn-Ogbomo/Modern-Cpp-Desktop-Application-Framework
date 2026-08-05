#include <cmath>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <numbers>

#include "../include/util.hpp"
#include "../include/board.hpp"

using namespace std::numbers;

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

	const auto a = sf::Angle{ sf::radians(static_cast<float>(v1 * 2.0f * pi / (v2 - 1.0f) - (pi / 2.0f))) };

	auto a_radians = a.asRadians();
	auto pos = sf::Vector2f{ center_x + radius * std::cos(a_radians) - (pos_card.x / 2.0f), center_y + (radius * std::sin(a_radians)) - pos_card.y / 2.0f };

	front.setPosition(pos);
	back.setPosition(pos);
}

Board::Board(Deck& d)
{
	for (auto index = 0; auto& pile : piles)
	{
		Util::allocate(pile);
		auto& [state, cards] = pile;

		for (auto& [card, rank] : cards)
		{
			card = d.draw();
			rank = Rank_Lib::ranks[index];

			auto [face, reverse] = card.img();
			position_card(face, reverse, rank, index, total_piles);
		}

		++index;
	}

	auto& [state, cards] = piles.back();
	state = true;

	auto& [card, rank] = piles.back().second.back();
	card.position() = Card_State::face_up;
}

auto Board::operator ()(sf::Vector2f cursor_pos) ->std::array < std::pair<bool, std::deque<std::pair<Card, Rank_Lib::Rank>>>, total_piles>::iterator
{
	return std::find_if(piles.begin(), piles.end(), [&](auto& p) {
		const auto& [card_size_x, card_size_y] = piles.back().second.back().first.img().first.getLocalBounds().size;
		const auto& [card_pos_x, card_pos_y] = p.second.back().first.img().first.getPosition();
		return (p.first && cursor_pos.x >= card_pos_x && cursor_pos.x <= card_pos_x + card_size_x
			&& cursor_pos.y >= card_pos_y && cursor_pos.y <= card_pos_y + card_size_y);
		});
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& pile : piles)
	{
		auto& [state, cards] = pile;

		for (const auto& [card, rank] : cards)
		{
			target.draw(card);
		}
	}
}