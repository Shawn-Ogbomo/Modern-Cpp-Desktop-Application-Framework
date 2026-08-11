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
	Deck(const Deck&) = delete;
	auto operator = (const Deck&)->Deck & = delete;
	Deck(Deck&&) = delete;
	auto operator = (Deck&&)->Deck & = delete;
	auto draw() -> Card;
private:
	auto shuffle() -> void;
	Card_Manager cm;
	std::vector<Card> cards;
};

#endif // DECK_HPP