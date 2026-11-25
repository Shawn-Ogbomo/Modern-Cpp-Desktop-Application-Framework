#ifndef COMPONENT_MANAGER_HPP
#define COMPONENT_MANAGER_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>

#include <span>

#include "../include/board.hpp"
#include "../include/music_player.hpp"

class Exit_Menu;
class Game_State_Menu;
class Confirmation_Menu;
class Input_Menu;

class Component_Manager
{
public:
    Component_Manager(std::span<bool> bsas, std::span<Board> bs
        , std::span<sf::Clock> cs,std::span<Exit_Menu>ems
        , std::span<Music_Player> mps, std::span<sf::RenderWindow> rws
        , std::span<Game_State_Menu> gsms, std::span<Confirmation_Menu> cms
        ,std::span<Input_Menu> ims)
        : app_state{ bsas }, board{ bs }, cl{ cs }, em{ ems }
        , mp{ mps }, rw{ rws }, gsm{ gsms }, cm{ cms }, im{ims}
    {}

    auto enable_exit_menu() const& ->void;
    auto enable_game_state_menu()const& ->void;
    auto enable_confirmation_menu()const& ->void;

    auto disable_exit_menu() const& -> void;
    auto disable_game_state_menu() const& -> void;
    auto disable_confirmation_menu() const& -> void;

    auto enable_clock() const& ->void;
    auto enable_board() const& ->void;
    auto enable_music_player() const& ->void;

    auto disable_clock() const& -> void;
    auto disable_board() const& -> void;
    auto disable_music_player() const& -> void;
    
    auto disable_text_box() const& ->void;
    auto disable_text_box_input() const& ->void;

    auto restart_game() & -> void;
    auto close_window()const& ->void;
private:
    std::span<bool> app_state;
    std::span<Board> board;
    std::span<sf::Clock> cl;
    std::span<Exit_Menu> em;
    std::span<Music_Player> mp;
    std::span<sf::RenderWindow>rw;
    std::span<Game_State_Menu>gsm;
    std::span<Confirmation_Menu>cm;
    std::span<Input_Menu>im;
};

auto enable_components(Component_Manager& cm) -> void;
auto disable_components(Component_Manager& cm) -> void;
auto disable_confirmation_menus(Component_Manager& cm) -> void;

#endif // COMPONENT_MANAGER_HPP