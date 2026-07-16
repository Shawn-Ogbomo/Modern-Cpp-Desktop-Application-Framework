#include <cmath>
#include <iterator>
#include <iostream>
#include <algorithm>

#include "../include/util.hpp"
#include "../include/board.hpp"

auto Board::allocate(std::pair<bool, std::deque<std::pair<Card, Rank_lib::Rank>>>& stack)->void
{
	std::fill_n(std::back_inserter(stack.second), 4, std::pair{ Card{},Rank_lib::Rank{} });
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& pile : piles)
	{
		for (const auto& [card, rank] : pile.second)
		{
			target.draw(card);
		}
	}
}

Board::Board(Deck& d)
{
	const auto center_x = 500.0f;
	const auto center_y = 385.0f;
	const auto radius = 300.0f;
	constexpr auto pi = 3.14159265358979323846;

	auto index = 0;

	for (auto& pile : piles)
	{
		allocate(pile);

		for (auto& [card, rank] : pile.second)
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

			face.setPosition(sf::Vector2f{ center_x + radius * std::cos(a.asRadians()) - (face.getLocalBounds().size.x) / 2, center_y + (radius * std::sin(a.asRadians())) - face.getLocalBounds().size.y / 2 });
			reverse.setPosition(sf::Vector2f{ center_x + radius * std::cos(a.asRadians()) - (reverse.getLocalBounds().size.x) / 2, center_y + (radius * std::sin(a.asRadians())) - reverse.getLocalBounds().size.y / 2 });
		}

		++index;
	}

	auto& [card, rank] = piles[12].second.back();
	card.position() = Card_State::face_up;
	piles[12].first = true;
}

auto Board::operator ()(sf::Vector2f cursor_pos)->std::array < std::pair<bool, std::deque<std::pair<Card, Rank_lib::Rank>>>, total_piles>::iterator
{
	//this operator is only valid while there are less than 4 kings face up in the center pile
	//get a count of face up kings in the center pile...
	//IF the cursor within the bounds of a card???
	// get an iterator to the card
	return std::find_if(piles.begin(), piles.end(), [&cursor_pos](auto& c) {
		return (cursor_pos.x >= c.second[0].first.img().first.getPosition().x && cursor_pos.x <= c.second[0].first.img().first.getPosition().x + c.second[0].first.img().first.getLocalBounds().size.x
			&& cursor_pos.y >= c.second[0].first.img().first.getPosition().y && cursor_pos.y <= c.second[0].first.img().first.getPosition().y + c.second[0].first.img().first.getLocalBounds().size.y);
		});

	// is it in bounds of the correct destination pile??
		//turn the shader effect on destination pile while the card is within bounds
	// use operator == to compare active card suit to destination pile suit

	//if the card is dropped in the correct pile move it from the source pile to the destination pile -- the back
		// move all cards starting from the back to the front if they are face up
	//turn off the shader when the card is not in bounds
}