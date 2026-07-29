#include "../include/card.hpp"

Card::Card(Suit s, Rank_lib::Rank r, const sf::Texture& f,  const sf::Texture& re, Card_State st)
	:suit{ s },
	rank{ r },
	face{f},
	reverse{re},
	state{ st } {
}