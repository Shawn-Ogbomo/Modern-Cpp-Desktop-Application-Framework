#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../include/menu.hpp"
#include "../include/music_player.hpp"
#include "../include/state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

struct Button : public sf::Drawable
{
public:
    virtual ~Button() = default;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

struct Forms
{
public:
    Forms(const Texture_Forms& txtrs) :form_1{ txtrs.f1 }
        , form_2{ txtrs.f2 }, form_3{ txtrs.f3 }
    {}

    sf::Sprite form_1;
    sf::Sprite form_2;
    sf::Sprite form_3;
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

auto display_manager(const auto& button, sf::RenderTarget& target) -> void
{
    static_cast<bool>(button.setting) ? target.draw(button.forms.form_3)
        : target.draw(button.forms.form_1);
}

struct Music_Player;

struct Media_Button : public Button
{
public:
    Media_Button(const Texture_Forms& txtrs, auto val, sf::Vector2f pos) :forms{ txtrs }
    {
        update_button(name, forms, val, pos);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        display_manager(*this, target);
    }

    Forms forms;

    Button_Names::Media name{};
    ButtonMode setting{};
};

struct Game_State_Menu;

struct Game_State_Button : public Button
{
public:
    Game_State_Button(const Texture_Forms& txtrs
        , auto val, sf::Vector2f pos, std::string_view target_label) :forms{ txtrs }
    {
        update_button(name, forms, val, pos);
        label.setString(target_label);
        label.setFillColor({ 236,203,180 });

        label.setCharacterSize(22);
        label.setPosition({ pos.x, pos.y });
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        display_manager(*this, target);
        target.draw(label);
    }

    Forms forms;

    sf::Text label{ Util::load_font() };
    Button_Names::Game_State name{};
    ButtonMode setting{};
};

struct Exit_Menu;

struct Exit_Menu_Button : public Button
{
public:
    Exit_Menu_Button(const Texture_Forms& txtrs
        , auto val, sf::Vector2f pos, std::string_view target_label) :forms{ txtrs }
    {
        update_button(name, forms, val, pos);
        label.setString(target_label);
        label.setFillColor({ 236,203,180 });

        label.setCharacterSize(22);
        label.setPosition({ pos.x, pos.y });
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        display_manager(*this, target);
        target.draw(label);
    }

    Forms forms;

    sf::Text label{ Util::load_font() };
    Button_Names::Game_State name{};
    ButtonMode setting{};
};

struct Confirmation_Menu;

struct Confirmation_Button : public Button
{
public:
    Confirmation_Button(const Texture_Forms& txtrs
        , auto val, sf::Vector2f pos, std::string_view target_label) :forms{ txtrs }
    {
        update_button(name, forms, val, pos);
        label.setString(target_label);
        label.setFillColor({ 236,203,180 });

        label.setCharacterSize(22);
        label.setPosition({ pos.x, pos.y });
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        display_manager(*this, target);
        target.draw(label);
    }

    Forms forms;

    sf::Text label{ Util::load_font() };
    Button_Names::General name{};
    ButtonMode setting{};
};

#endif //BUTTON_HPP