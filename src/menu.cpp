#include "../include/menu.hpp"

namespace B_N = Button_Names;

Game_State_Menu::Game_State_Menu()
{
    gb_interface.load_textures();
    state_buttons.reserve(2);

    state_buttons.push_back({ gb_interface.textures,B_N::Status::pause, {417,800}, "Pause" });
    state_buttons.push_back({ gb_interface.textures,B_N::Status::resume, {417,800}, "Resume" });
}

void Game_State_Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(state_buttons[0]);
}