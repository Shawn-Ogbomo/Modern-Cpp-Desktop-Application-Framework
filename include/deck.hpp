#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include <algorithm>

#include "../include/card.hpp"
#include "../include/random_number_gen.hpp"

class Deck
{
public:
	Deck();
	auto draw() -> Card;
private:
	auto shuffle() -> void;
	Card_Manager cm;
	std::vector<Card> cards;
};

#endif // DECK_HPP