#ifndef CARD_HPP
#define CARD_HPP

#include <utility>
#include <functional>

#include <SFML/Graphics.hpp>

#include "../include/rank.hpp"
#include "../include/suit.hpp"
#include "../include/state.hpp"
#include "../include/texture_manager.hpp"

class Card : public sf::Drawable
{
	sf::Texture t;
public:
	Card() = default;
	explicit Card(std::string_view card_name, sf::Texture& f, sf::Texture& re, Card_State st = Card_State::face_down);
	auto position() -> Card_State& { return state; };
	auto value()const -> Rank_Lib::Rank { return rank; }
	auto img() -> std::pair<sf::Sprite&, sf::Sprite&> { return{ std::ref(face),std::ref(reverse) }; }
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const { state == Card_State::face_up ? target.draw(face) : target.draw(reverse); }
	Suit suit{};
	Card_State state{};
	Rank_Lib::Rank rank{};
	sf::Sprite face{ t };
	sf::Sprite reverse{ t };
};

#endif // CARD_HPP