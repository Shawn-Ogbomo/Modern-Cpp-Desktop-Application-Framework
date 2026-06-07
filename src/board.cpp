#include <cmath>
#include <iterator>
#include <iostream>
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
	const auto center_x = 500.0f;
	const auto center_y = 385.0f;
	const auto radius = 300.0f;
	constexpr auto pi = 3.14159265358979323846;

	for (auto& pile : piles)
	{
		allocate(pile);

		for (auto& [card, rank] : pile)
		{
			card = d.draw();
			rank = Rank_lib::ranks[index];
			auto& [face, reverse] = card.img();

			if (rank == Rank_lib::Rank::king)
			{
				auto center = sf::Vector2f{ (1000 - face.getLocalBounds().size.x) / 2, ((770 - face.getLocalBounds().size.y) / 2) };
				face.setPosition(center);
				reverse.setPosition(center);
				continue;
			}

			sf::Angle a{ sf::radians(index * 2.0f * pi / (total_piles - 1) - (pi / 2.0f)) };

			face.setPosition(sf::Vector2f{ center_x + radius * std::cos(a.asRadians()) - (face.getLocalBounds().size.x) / 2, center_y + (radius * std::sin(a.asRadians())) - face.getLocalBounds().size.y / 2 });
			reverse.setPosition(sf::Vector2f{ center_x + radius * std::cos(a.asRadians()) - (reverse.getLocalBounds().size.x) / 2, center_y + (radius * std::sin(a.asRadians())) - reverse.getLocalBounds().size.y / 2 });
		}

		++index;
	}

	auto& [card, rank] = piles[12].back();
	card.position() = Card_State::face_up;
}