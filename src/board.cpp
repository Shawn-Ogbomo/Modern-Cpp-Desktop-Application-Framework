#include <iostream>
#include <iterator>
#include <algorithm>

#include "../headers/util.hpp"
#include "../headers/board.hpp"

auto Board::allocate(std::vector<std::pair<Card, Rank_lib::Rank>>& stack)->void
{
	stack.reserve(4);
	std::fill_n(std::back_inserter(stack), 4, std::pair{ Card{}, Rank_lib::Rank{} });
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& pile : piles)
	{
		for (const auto& [card, rank] : pile)
		{
			target.draw(card);
		}
	}
}

Board::Board(Deck& d)
{
	auto index = 0;
	auto r = sf::Angle{ sf::degrees(30) };

	for (auto& pile : piles)
	{
		allocate(pile);

		for (auto& [card, rank] : pile)
		{
			card = d.draw();
			rank = Rank_lib::ranks[index];
			auto& [face, reverse] = card.img();

			if (rank == Rank_lib::Rank::ace)
			{
				auto coords_ace_pile = sf::Vector2f{ 543.245f , 194 };
				face.setPosition(coords_ace_pile);
				reverse.setPosition(coords_ace_pile);
			}

			else if (rank == Rank_lib::Rank::king)
			{
				auto center = sf::Vector2f{ (1000 - face.getLocalBounds().size.x) / 2, (900 - face.getLocalBounds().size.y - 105 ) / 2};
				face.setPosition(center);
				reverse.setPosition(center);
				continue;
			}

			else if (auto prev_pile = Util::prev(index, piles); prev_pile != std::end(piles))
			{
				const auto& [card_prev, rank_prev] = prev_pile[0].back().first.img();
				auto coords_bottom_right = card_prev.getTransform().transformPoint(sf::Vector2f{ 96, 144 });
				face.setPosition(coords_bottom_right);
				reverse.setPosition(coords_bottom_right);
			}

			face.setOrigin(sf::Vector2f{ 0,144 });
			reverse.setOrigin(sf::Vector2f{ 0,144 });

			reverse.rotate(r);
			face.rotate(r);
		}

		r += sf::Angle{ sf::degrees(30) };
		++index;
	}

	auto& [card, rank] = piles[12].back();
	card.position() = Card_State::face_up;
}