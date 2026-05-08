#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include "../headers/card.hpp"
#include "../headers/board.hpp"
#include "../headers/exceptions.hpp"

namespace Util {
	auto check_stream(std::istream& is, const std::string& message, const std::string& message2 = "") -> void;

	//returns the previous pile on the board
	auto prev(int pos, std::array<std::array<std::pair<Card, Rank_lib::Rank>, Board::cards_pile>, Board::total_piles>& vals) -> std::array<std::array<std::pair<Card, Rank_lib::Rank>, Board::cards_pile>, Board::total_piles>::iterator;
}
#endif //UTIL_HPP