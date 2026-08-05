#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <chrono>

#include "../include/card.hpp"
#include "../include/board.hpp"
#include "../include/exceptions.hpp"

namespace Util
{
	auto check_stream(const std::istream& is, const std::filesystem::path& p, const std::string& message = "", const std::string& message2 = "") -> void;
	auto load_font(const std::filesystem::path& p, sf::Font& f) -> void;
	auto delay_time(const sf::Clock& c, std::chrono::microseconds ms) -> void;
	auto local_time() -> std::string;

	auto allocate(auto& stack) -> void
	{
		auto& [state, cards] = stack;
		std::ranges::fill_n(std::back_inserter(cards), Board::cards_pile, std::pair{ Card{},Rank_Lib::Rank{} });
	}

	inline auto to_int(auto b) -> int
	{
		return static_cast<int>(b);
	}
}

#endif // UTIL_HPP