#include "../headers/card.hpp"

Card::Card(Suit s, Rank_lib::Rank r, const sf::Texture& f, const sf::Texture& re, State st)
	:suit{ s },
	rank{ r },
	face{ f },
	reverse{ re },
	state{ st } {}

void Card::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	state == State::face_up ? target.draw(face) : target.draw(reverse);
}