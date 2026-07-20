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
	auto allocate(std::pair<bool, std::deque<std::pair<Card, Rank_lib::Rank>>>& stack) -> void;
	auto delay_time(const sf::Clock& c, std::chrono::microseconds ms) -> void;
	auto position_card(sf::Sprite& front, sf::Sprite& back, Rank_lib::Rank rank, int v1, int v2) -> void;

}

#endif // UTIL_HPP