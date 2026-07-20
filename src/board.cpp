#include <cmath>
#include <iterator>
#include <iostream>
#include <algorithm>
#include <numbers>
#include "../include/util.hpp"
#include "../include/board.hpp"

using namespace std::numbers;

Board::Board(Deck& d)
{
	const auto center_x = 500.0f;
	const auto center_y = 385.0f;
	const auto radius	 = 300.0f;

	for (auto index = 0; auto& pile : piles)
	{
		Util::allocate(pile);
		auto& [state, cards] = pile;

		for (auto& [card, rank] : cards)
		{
			card = std::move(d.draw());
			rank = Rank_lib::ranks[index];

			auto [face, reverse] = card.img();

			if (rank == Rank_lib::Rank::king)
			{
				auto center = sf::Vector2f{ (1000 - face.getLocalBounds().size.x) / 2, ((770 - face.getLocalBounds().size.y) / 2) };
				face.setPosition(center);
				reverse.setPosition(center);
				continue;
			}

			sf::Angle a{ sf::radians(static_cast<float>(index * 2.0f * pi / (total_piles - 1.0f) - (pi / 2.0f))) };
			
			auto a_radians = a.asRadians();
			auto pos_card = face.getLocalBounds().size;
			auto pos = sf::Vector2f{ center_x + radius * std::cos(a_radians) - (pos_card.x / 2.0f), center_y + (radius * std::sin(a_radians)) - pos_card.y / 2.0f };

			face.setPosition(pos );
			reverse.setPosition(pos);
		}

		++index;
	}

	auto& [state, cards] = piles.back();
	state = true;

	auto& [card, rank] = piles.back().second.back();
	card.position() = Card_State::face_up;
}

auto Board::operator ()(sf::Vector2f cursor_pos)->std::array < std::pair<bool, std::deque<std::pair<Card, Rank_lib::Rank>>>, total_piles>::iterator
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