#ifndef  BOARD_HPP
#define  BOARD_HPP

#include <array>
#include <utility>
#include "../headers/deck.hpp"
#include "../headers/board.hpp"

struct Board
{
	static constexpr auto total_piles = 13;
public:
	explicit Board(Deck& d);
	Board(const Board&) = delete;
	auto allocate(std::vector<std::pair<Card, Rank_lib::Rank>>& stack) -> void;
	std::array<std::vector<std::pair<Card, Rank_lib::Rank>>, total_piles> piles{};
};

#endif //BOARD