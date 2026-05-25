#ifndef CARD_HPP
#define CARD_HPP

#include <utility>
#include <functional>

#include <SFML/Graphics.hpp>

#include "../headers/rank.hpp"
#include "../headers/suit.hpp"
#include "../headers/state.hpp"
#include "../headers/texture_manager.hpp"

class Card : public sf::Drawable
{
	sf::Texture default;
public:
	Card() = default;
	explicit Card(Suit s, Rank_lib::Rank r, const sf::Texture& f, const sf::Texture& re, Card_State st = Card_State::face_down);
	auto position() -> Card_State& { return state; };
	auto value()const -> Rank_lib::Rank { return rank; }
	auto img() -> std::pair<sf::Sprite&, sf::Sprite&> { return{ std::ref(face),std::ref(reverse) }; }
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const { state == Card_State::face_up ? target.draw(face) : target.draw(reverse); }
private:
	Suit suit{};
	Rank_lib::Rank rank{};
	sf::Sprite face{default};
	sf::Sprite reverse{default};
	Card_State state{};
};

#endif //CARD_HPP