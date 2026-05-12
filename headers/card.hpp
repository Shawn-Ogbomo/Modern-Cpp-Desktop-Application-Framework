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
public:
	Card() = default;
	explicit Card(Suit s, Rank_lib::Rank r, const sf::Texture& f, const sf::Texture& re, State st = State::face_down);
	auto position() -> State& { return state; };
	auto value()const -> Rank_lib::Rank { return rank; }
	auto img() -> std::pair<sf::Sprite&, sf::Sprite&> { return{ std::ref(face),std::ref(reverse) }; }

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		state == State::face_up ? target.draw(face) : target.draw(reverse);
	}

private:
	Suit suit{};
	Rank_lib::Rank rank{};
	sf::Sprite face{ get_texture_manager().textures.back() };
	sf::Sprite reverse{ get_texture_manager().textures.back() };
	State state{};
};

#endif //CARD_HPP