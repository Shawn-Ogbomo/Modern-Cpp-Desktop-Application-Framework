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
}

#endif // UTIL_HPP