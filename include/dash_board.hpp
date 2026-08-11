#ifndef  DASH_BOARD_HPP
#define  DASH_BOARD_HPP

#include "./music_player.hpp"
#include "./game_status.hpp"
#include "./time_status.hpp"

struct DashBoard : sf::Drawable
{
public:
	DashBoard()
	{
		dash.setFillColor(sf::Color{ 228, 193, 156 });
		dash.setPosition(sf::Vector2f{ 0.f,770.f });
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(dash);
		target.draw(gs);
		target.draw(ts);
		target.draw(mp);
	}

	Game_Status gs;
	Time_Status ts;
	Music_Player mp;
	sf::RectangleShape dash{ sf::Vector2f{ 1000.f,130.f } };
};

#endif	//DASH_BOARD_HPP