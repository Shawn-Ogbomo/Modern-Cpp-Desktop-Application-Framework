#include <cmath>
#include <iterator>
#include <iostream>
#include <algorithm>

#include "../include/util.hpp"
#include "../include/board.hpp"

Board::Board(Deck& d)
{
	for (auto index = 0; auto& pile : piles)
	{
		Util::allocate(pile);
		auto& [state, cards] = pile;

		for (auto& [card, rank] : cards)
		{
			card = std::move(d.draw());
			rank = Rank_Lib::ranks[index];

			auto [face, reverse] = card.img();
			Util::position_card(face, reverse, rank, index, total_piles);
		}

		++index;
	}

	auto& [state, cards] = piles.back();
	state = true;

	auto& [card, rank] = piles.back().second.back();
	card.position() = Card_State::face_up;
}

auto Board::operator ()(sf::Vector2f cursor_pos)->std::array < std::pair<bool, std::deque<std::pair<Card, Rank_Lib::Rank>>>, total_piles>::iterator
{
	 const auto& [card_size_x, card_size_y] = piles.back().second.back().first.img().first.getLocalBounds().size;

	return std::find_if(piles.begin(), piles.end(), [&](auto& p) {
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