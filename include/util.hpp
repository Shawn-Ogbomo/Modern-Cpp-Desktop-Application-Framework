#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>

#include "../include/card.hpp"
#include "../include/board.hpp"
#include "../include/exceptions.hpp"

namespace Util
{
	auto check_stream(const std::istream& is, const std::filesystem::path&p, const std::string& message ="", const std::string& message2 = "") -> void;

	//returns the previous pile on the board
	auto prev(int pos, std::array<std::vector<std::pair<Card, Rank_lib::Rank>>, Board::total_piles>& piles)
		-> std::array < std::vector<std::pair<Card, Rank_lib::Rank>>, Board::total_piles>::iterator;

	auto load_font(const std::filesystem::path& p, sf::Font& f) -> void;
}

#endif // UTIL_HPP