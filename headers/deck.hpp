#ifndef DECK_HPP
#define DECK_HPP

#include <vector>
#include <algorithm>

#include "../headers/card.hpp"
#include "../headers/random_number_gen.hpp"

class Deck
{
public:
	Deck();
	Deck(const Deck&) = delete;
	auto operator = (const Deck&)->Deck & = delete;
	Deck(const Deck&&) = delete;
	auto operator = (const Deck&&)->Deck & = delete;
	
	auto draw() -> Card;
	auto shuffle() -> void { std::shuffle(cards.begin(), cards.end(), Random_Number_Gen::g); }
private:
	std::vector<Card> cards;
};

#endif // DECK_HPP