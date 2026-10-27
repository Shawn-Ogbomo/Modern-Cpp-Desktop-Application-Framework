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
    auto local_time() -> std::string;
    auto allocate(Pile& stack) -> void;
}

#endif // UTIL_HPP