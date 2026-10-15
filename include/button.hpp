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

auto update_button(Button_Names::Is_Valid_Enum auto& internal_name
    , std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& forms
    , Button_Names::Is_Valid_Enum auto val, sf::Vector2f pos) -> void
{
    internal_name = val;

    auto& [form_1, form_2, form_3] = forms;

    form_1.setPosition(pos);
    form_2.setPosition(pos);
    form_3.setPosition(pos);
}

auto display_manager(const auto& button, sf::RenderTarget& target) -> void
{
    static_cast<bool>(button.setting) ? target.draw(std::get<2>(button.forms))
        : target.draw(std::get<0>(button.forms));
}

struct Music_Player;

struct Media_Button : public Button
{
public:
    Media_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs, auto val, sf::Vector2f pos) :forms{ txtrs }
    {
        update_button(name, forms, val, pos);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        display_manager(*this, target);
    }

    std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{ default_texture()
        ,default_texture(),default_texture() };

    Button_Names::Media name{};
    ButtonMode setting{};
};

struct Game_State_Menu;

struct Game_State_Button : public Button
{
public:
    Game_State_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs
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

    std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{ default_texture()
        ,default_texture(),default_texture() };

    sf::Text label{ Util::load_font() };
    Button_Names::Game_State name{};
    ButtonMode setting{};
};

#endif //BUTTON_HPP