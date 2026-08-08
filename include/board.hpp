#ifndef  BOARD_HPP
#define  BOARD_HPP

#include <array>
#include <utility>
#include <deque>

#include "../include/deck.hpp"

struct Board : public sf::Drawable
{
	static constexpr auto total_piles = 13;
	static constexpr auto cards_pile = 4;
	using Board_It = std::array <std::pair<bool, std::deque<std::pair<Card, Rank_Lib::Rank>>>, Board::total_piles>::iterator;
public:
	explicit Board(Deck& d);
	Board(const Board&) = delete;
	auto operator =(const Board&) ->Board & = delete;
	Board(Board&&) = delete;
	auto operator =(Board&&) ->Board & = delete;
	auto operator ()(Board_It src, Board_It dest,sf::Vector2f pos)->Board_It;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::array <std::pair<bool, std::deque<std::pair<Card, Rank_Lib::Rank>>>, total_piles > piles{};
	Board_It source_pile;
	Board_It destination_pile;
};

#endif // BOARD_HPP 