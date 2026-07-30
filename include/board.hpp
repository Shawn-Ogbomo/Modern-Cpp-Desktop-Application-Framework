#ifndef  BOARD_HPP
#define  BOARD_HPP

#include <array>
#include <utility>
#include <deque>

#include "../include/deck.hpp"

struct Board : public sf::Drawable
{
	static constexpr auto total_piles = 13;
public:
	explicit Board(Deck& d);
	Board(const Board&) = delete;
	auto operator =(const Board&) ->Board & = delete;
	Board(Board&&) = delete;
	auto operator =(Board&&) ->Board & = delete;
	auto operator ()(sf::Vector2f cursor_pos = {})->std::array < std::pair<bool, std::deque<std::pair<Card, Rank_lib::Rank>>>, total_piles>::iterator;
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	std::array <std::pair<bool, std::deque<std::pair<Card, Rank_lib::Rank	>>>, total_piles > piles{};
};

#endif // BOARD_HPP 