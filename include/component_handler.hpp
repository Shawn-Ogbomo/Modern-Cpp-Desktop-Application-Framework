#ifndef COMPONENT_HANDLER_HPP
#define COMPONENT_HANDLER_HPP

#include "../include/menu.hpp"
#include "../include/refs.hpp"

auto component_click_listener(auto buttons, auto& spn, sf::Vector2f cursor_pos) -> void
{
    auto button = std::ranges::find_if(buttons, [&](const auto& b) {
        return std::get<0>(b.forms).getGlobalBounds().contains(cursor_pos);
        });

    if (button != std::end(buttons))

    {
        button->setting = ButtonMode::on;
        spn = { &(*button) ,1 };
    }
};

struct Game_State_Button;

auto component_release_listener(const auto& menu, Refs_Components& r_c, auto& spn
    , sf::Vector2f cursor_pos) -> void
{
    if (!spn.empty())
    {
        if (menu && std::get<0>(spn.front().forms).getGlobalBounds().contains(cursor_pos))
        {
            r_c.sp7_gsm.front().update_game_state(spn.front().name, r_c);
        }

        spn.front().setting = ButtonMode::off;
    }

    spn = std::span<Game_State_Button>{};;
};

#endif //COMPONENT_HANDLER_HPP