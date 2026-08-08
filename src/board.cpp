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

	const auto a = sf::Angle{ sf::radians(v1 * 2.0f * pi / (v2 - 1.0f) - (pi / 2.0f)) };

	auto a_radians = a.asRadians();
	auto pos = sf::Vector2f{ center_x + radius * std::cos(a_radians) - (pos_card.x / 2.0f), center_y + (radius * std::sin(a_radians)) - pos_card.y / 2.0f };

	front.setPosition(pos);
	back.setPosition(pos);
}

Board::Board(Deck& d)
	:source_pile{std::end(piles)},
	destination_pile{std::end(piles)}
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

auto Board::operator ()(Board_It src, Board_It dest, sf::Vector2f pos) ->Board_It
{	
	 return std::find_if(piles.begin(), piles.end(), [&](auto& p) {
		 auto& [active, pile] = p;
		 const auto& [face, reverse] = pile.back().first.img();
		 return (active && face.getGlobalBounds().contains(pos) ) || src != std::end(piles) 
			 && face.getGlobalBounds().findIntersection(src->second.back().first.img().first.getGlobalBounds());
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