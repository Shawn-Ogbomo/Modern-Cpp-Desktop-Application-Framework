#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>

#include <vector>

#include "../include/button.hpp"
#include "../include/state.hpp"
#include "../include/texture_manager.hpp"

class Game_State_Button;

struct Menu : public sf::Drawable
{
public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual ~Menu() = default;
};

class Game_State_Menu : public Menu
{
public:
    Game_State_Menu();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    General_Buttons gb_interface;
    std::vector<Game_State_Button> state_buttons;
};

#endif //MENU_HPP