#ifndef UTIL_HPP
#define UTIL_HPP

#include <chrono>
#include <string>

#include "../include/board.hpp"
#include "../include/card.hpp"
#include "../include/exceptions.hpp"

namespace Util
{
    auto load_font() -> const sf::Font&;
    auto delay_time(const sf::Clock& c, std::chrono::microseconds ms) -> void;
    auto local_time() -> std::string;
    auto allocate(std::tuple<bool, std::deque<Card>, Rank_Lib::Rank, sf::Vector2f>& stack) -> void;
}

#endif // UTIL_HPP