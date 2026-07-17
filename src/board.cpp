#include <cmath>
#include <iterator>
#include <iostream>
#include <algorithm>

#include "../include/util.hpp"
#include "../include/board.hpp"

auto Board::allocate(std::pair<bool, std::deque<std::pair<Card, Rank_lib::Rank>>>& stack)->void
{
	auto& [state, cards] = stack;
	std::fill_n(std::back_inserter(cards), 4, std::pair{ Card{},Rank_lib::Rank{} });
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

			face.setPosition(sf::Vector2f{ center_x + radius * std::cos(a.asRadians()) - (face.getLocalBounds().size.x) / 2, center_y + (radius * std::sin(a.asRadians())) - face.getLocalBounds().size.y / 2 });
			reverse.setPosition(sf::Vector2f{ center_x + radius * std::cos(a.asRadians()) - (reverse.getLocalBounds().size.x) / 2, center_y + (radius * std::sin(a.asRadians())) - reverse.getLocalBounds().size.y / 2 });
		}

		++index;
	}

	auto& [state, cards] = piles.back();
	state = true;

	auto& [card, rank] = piles.back().second.back();
	card.position() = Card_State::face_up;
}

auto Board::operator ()(sf::RenderWindow& rw, sf::RectangleShape& r, sf::Shader& effect, sf::Vector2f cursor_pos)->std::array < std::pair<bool, std::deque<std::pair<Card, Rank_lib::Rank>>>, total_piles>::iterator
{
	return std::find_if(piles.begin(), piles.end(), [&cursor_pos](auto& c) {
		return (cursor_pos.x >= c.second[0].first.img().first.getPosition().x && cursor_pos.x <= c.second[0].first.img().first.getPosition().x + c.second[0].first.img().first.getLocalBounds().size.x
			&& cursor_pos.y >= c.second[0].first.img().first.getPosition().y && cursor_pos.y <= c.second[0].first.img().first.getPosition().y + c.second[0].first.img().first.getLocalBounds().size.y);
		});

	//this is variable
	r.setPosition(sf::Vector2f{ 452 - 10, 313 - 10 });
	rw.draw(r, &effect);
}