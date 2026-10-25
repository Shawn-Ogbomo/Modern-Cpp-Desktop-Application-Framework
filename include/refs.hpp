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
struct Confirmation_Menu;

struct Refs_Components
{
public:
    Refs_Components(std::span<bool> bsas, std::span<Board> bs, std::span<sf::Clock> cs,
        std::span<Exit_Menu>ems, std::span<Music_Player> mps, std::span<sf::RenderWindow> rws
        , std::span<Game_State_Menu> gsms, std::span<Confirmation_Menu> cms)
        : sp1_b{ bsas }, sp2_b{ bs }, sp3_c{ cs }, sp4_em{ ems }
        , sp5_mp{ mps }, sp6_rw{ rws }, sp7_gsm{ gsms }, sp8_cm{ cms }
    {}

    std::span<bool> sp1_b;
    std::span<Board> sp2_b;
    std::span<sf::Clock> sp3_c;

    std::span<Exit_Menu> sp4_em;
    std::span<Music_Player> sp5_mp;
    std::span<sf::RenderWindow>sp6_rw;
    std::span<Game_State_Menu>sp7_gsm;
    std::span<Confirmation_Menu>sp8_cm;
};

#endif // REFS_HPP