#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../include/state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

struct Forms
{
    Forms() = default;
    Forms(const Texture_Forms& txtrs) :form_1{ txtrs.f1 }
        , form_2{ txtrs.f2 }, form_3{ txtrs.f3 }
    {}

    sf::Sprite form_1{ default_texture() };
    sf::Sprite form_2{ default_texture() };
    sf::Sprite form_3{ default_texture() };
};

template<typename T>
struct Properties
{
    T name{};
    ButtonMode setting{};
};

template<typename T1, typename T2>
struct Menu_Properties
{
    Menu_Properties(ButtonMode bm
        = ButtonMode::off) :mode{ bm }
    {}

    T1 state_buttons;
    std::span<T2> spn;
    ButtonMode mode{};
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

template <typename T>
struct Button : sf::Drawable
{
    Button() = default;

    Button(const Texture_Forms& txtrs
        , auto val, sf::Vector2f pos
        , std::string_view target_label = "") : forms{ txtrs }
    {
        configure_button(*this, val, target_label, pos);
    }

    operator bool() const& { return static_cast<bool>(contents.setting); }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        display_manager(*this, target);
        target.draw(label);
    }

    Forms forms;
    sf::Text label{ Util::load_font() };
    Properties<T> contents;
};

template<typename T>
concept Is_Valid_Button = std::is_same_v<T, Button<Button_Names::Exit>>
|| std::is_same_v<T, Button<Button_Names::Game_State>>
|| std::is_same_v<T, Button<Button_Names::Confirm>>
|| std::is_same_v<T, Button<Button_Names::Media>>
|| std::is_same_v<T, Button<Button_Names::General>>
|| std::is_same_v<T, Button<Button_Names::Confirm_Input>>;

auto configure_button(Is_Valid_Button auto& button, Button_Names::Is_Valid_Enum auto val
    , std::string_view target_label, sf::Vector2f pos) -> void
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