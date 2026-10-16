#ifndef REFS_HPP
#define REFS_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include <span>

#include "../include/board.hpp"
#include "../include/menu.hpp"
#include "../include/music_player.hpp"

struct Exit_Menu;
struct Music_Player;
struct Game_State_Menu;

struct Refs_Components
{
public:
    explicit Refs_Components(sf::Clock& c, Board& b, bool& app_state, sf::RenderWindow& rw)
        : sp1_c{ &c,1 }, sp2_b{ &b,1 }, sp3_b{ &app_state, 1 }
    {
        sp7_rw = { &rw,1 };
    }

    std::span<sf::Clock> sp1_c;
    std::span<Board> sp2_b;
    std::span<bool> sp3_b;

    std::span<Music_Player> sp4_mp;
    std::span<Game_State_Menu>sp5_gsm;
    std::span<Exit_Menu> sp6_em;
    std::span<sf::RenderWindow>sp7_rw;
};

#endif // REFS_HPP