#ifndef  BOARD_HPP
#define  BOARD_HPP

#include <array>
#include <utility>
#include <deque>

#include "../include/deck.hpp"

struct Board : public sf::Drawable
{
	static constexpr auto cards_pile = 4;
	static constexpr auto total_piles = 13;
	using Pile_It = std::array <std::tuple<bool, std::deque<std::pair<Card, Rank_Lib::Rank>>,sf::Vector2f>, Board::total_piles>::iterator;
public:
	Board() = delete;
	explicit Board(Deck& d);
	Board(const Board&) = delete;
	auto operator =(const Board&) ->Board & = delete;
	Board(Board&&) = delete;
	auto operator =	(Board&&) ->Board & = delete;
	auto operator ()	(Pile_It src, sf::Vector2f pos)->Pile_It;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	Pile_It source_pile;
	Pile_It destination_pile;
	std::array <std::tuple<bool, std::deque<std::pair<Card, Rank_Lib::Rank>>,sf::Vector2f>, total_piles > piles{};
};

#endif // BOARD_HPP 