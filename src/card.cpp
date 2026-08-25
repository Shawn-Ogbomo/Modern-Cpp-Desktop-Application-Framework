#include <charconv>

#include "../include/card.hpp"
#include "../include/suit.hpp"

Card::Card(std::string_view card_name, const sf::Texture& f, const sf::Texture& re, Card_State st) : face{ f }, reverse{ re }, state{ st }
{
    const auto pos_suite_name_begin = (card_name.find_first_of("-") + 1);
    const auto count = (card_name.find_last_of("-") - 1) - (pos_suite_name_begin)+1;

    const auto& [suite_name, value] = (*suits.find(card_name.substr(pos_suite_name_begin, count)));

    suit = value;
    auto result = 0;

    std::from_chars(card_name.data() + (card_name.find_last_of("-") + 1), card_name.data() + card_name.size(), result);
    rank = static_cast<Rank_Lib::Rank>(result);
}