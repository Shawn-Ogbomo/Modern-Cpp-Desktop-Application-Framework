#ifndef UTIL_HPP
#define UTIL_HPP

#include <string>
#include <chrono>

#include "../include/card.hpp"
#include "../include/board.hpp"
#include "../include/exceptions.hpp"

namespace Util
{
    auto check_stream(const std::istream& is, std::filesystem::path& p, std::string& message, std::string& message2) -> void;
    auto load_font(const std::filesystem::path& p, sf::Font& f) -> void;
    auto delay_time(const sf::Clock& c, std::chrono::microseconds ms) -> void;
    auto local_time() -> std::string;
    auto allocate(std::tuple<bool, std::deque<Card>, Rank_Lib::Rank, sf::Vector2f>& stack) -> void;
}

#endif // UTIL_HPP