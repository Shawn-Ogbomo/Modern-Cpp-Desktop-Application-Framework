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

#endif //COMPONENT_HANDLER_HPP