#ifndef  BUTTON_HPP
#define BUTTON_HPP

#include "../headers/state.hpp"

struct Button : public sf::Drawable
{
public:
	explicit Button(const sf::Texture& t, const sf::Texture& t2, const sf::Texture& t3)
	{
		static ButtonState bs{};
		name = bs;
		++bs;

		forms.push_back(std::move(sf::Sprite{ t }));
		forms.push_back(std::move(sf::Sprite{ t2 }));
		forms.push_back(std::move(sf::Sprite{ t3 }));
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(forms[0]);
	}

	ButtonState name{};
	std::vector<sf::Sprite>forms;
};

#endif // BUTTON_HPP