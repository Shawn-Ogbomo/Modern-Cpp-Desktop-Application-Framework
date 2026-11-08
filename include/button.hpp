#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../include/state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

struct Button : public sf::Drawable
{
    virtual ~Button() = default;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

struct Forms
{
    Forms() = default;
    Forms(const Texture_Forms& txtrs) :form_1{ txtrs.f1 }
        , form_2{ txtrs.f2 }, form_3{ txtrs.f3 }
    {}

    sf::Sprite form_1{default_texture()};
    sf::Sprite form_2{ default_texture()};
    sf::Sprite form_3{ default_texture() };
};

template<typename T>
struct Properties
{
    T name{};
    ButtonMode setting{};
};

auto update_button(Button_Names::Is_Valid_Enum auto& internal_name
    , Forms& forms
    , Button_Names::Is_Valid_Enum auto val, sf::Vector2f pos) -> void
{
    internal_name = val;

    forms.form_1.setPosition(pos);
    forms.form_2.setPosition(pos);
    forms.form_3.setPosition(pos);
}

auto configure_button(auto& button, auto val, std::string_view target_label, sf::Vector2f pos) -> void
{
    update_button(button.contents.name, button.forms, val, pos);
    button.label.setString(target_label);
    button.label.setFillColor({ 236,203,180 });
    button.label.setCharacterSize(22);
    button.label.setPosition({ pos.x, pos.y });
}

auto display_manager(const auto& button, sf::RenderTarget& target) -> void
{
    static_cast<bool>(button.contents.setting) ? target.draw(button.forms.form_3)
        : target.draw(button.forms.form_1);
}

#endif //BUTTON_HPP