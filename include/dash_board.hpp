#ifndef  DASH_BOARD_HPP
#define  DASH_BOARD_HPP

#include "../include/menu.hpp"
#include "./music_player.hpp"
#include "./time_status.hpp"

struct DashBoard : sf::Drawable
{
public:
    DashBoard(std::shared_ptr<sf::Clock> shptr_c, std::shared_ptr<Board> shptr_b)
    {
        dash.setFillColor({ 33, 46, 82 });
        dash.setPosition(sf::Vector2f{ 0.f,770.f });
        ts.set_clock(shptr_c);
        gsm.set_clock(shptr_c);
        gsm.set_board(shptr_b);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(dash);
        target.draw(gsm);
        target.draw(ts);
        target.draw(mp);
    }

    Time_Status ts;
    Music_Player mp;
    Game_State_Menu gsm;
    sf::RectangleShape dash{ sf::Vector2f{ 1000.f,130.f } };
};

#endif	//DASH_BOARD_HPP