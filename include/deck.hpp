#ifndef DECK_HPP
#define DECK_HPP

#include <algorithm>
#include <vector>

#include "../include/card.hpp"
#include "../include/random_number_gen.hpp"

class Deck
{
public:
    Deck(const Card_Manager&cm);
    auto draw() & ->Card;
private:
    auto shuffle() & -> void;
    std::vector<Card> cards;
};

#endif // DECK_HPP