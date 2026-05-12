#include "../headers/card.hpp"

Card::Card(Suit s, Rank_lib::Rank r, const sf::Texture& f, const sf::Texture& re, State st)
	:suit{ s },
	rank{ r },
	face{ f },
	reverse{ re },
	state{ st } {}