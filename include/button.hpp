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

template<typename T>
concept Is_Valid_Button = std::derived_from<T, Button>;

template <typename T>
class Button_Interface
{
public:
    static auto operator()(auto t1, auto& t2) ->void { t1->operator()(t2); }

    static auto operator()(Is_Valid_Button auto b) -> void { on = (!(static_cast<bool>(b.name))) ? false : true; }

    static auto click_listener(auto buttons, sf::Vector2f cursor_pos) -> void
    {
        if (on)
        {
            auto button = std::ranges::find_if(buttons, [&](const auto& b) {
                return std::get<0>(b.forms).getGlobalBounds().contains(cursor_pos);
                });

            if (button != std::end(buttons))
            {
                button->setting = ButtonMode::on;
                ob = &(*button);
            }
        }
    }

    static auto release_listener(auto& obj, sf::Vector2f cursor_pos) -> void
    {
        if (ob)
        {
            if (std::get<0>((*ob)->forms).getGlobalBounds().contains(cursor_pos))
            {
                operator()(*ob, obj);
            }

            ob.value()->setting = ButtonMode::off;
            ob = std::nullopt;
        }
    }

    static auto update_button(Button_Names::Is_Valid_Enum auto& internal_name
        , std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& forms
        , Button_Names::Is_Valid_Enum auto val, sf::Vector2f pos) -> void
    {
        internal_name = val;

        auto& [form_1, form_2, form_3] = forms;

        form_1.setPosition(pos);
        form_2.setPosition(pos);
        form_3.setPosition(pos);
    }

    static auto display_manager(const auto& button, sf::RenderTarget& target) -> void
    {
        static_cast<bool>(button.setting) ? target.draw(std::get<2>(button.forms))
            : target.draw(std::get<0>(button.forms));
    }
private:
    static constinit inline auto ob = std::optional<T*>{};
    static constinit inline auto on = true;
};

class Music_Player;

struct Media_Button : public Button
{
public:
    Media_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs, auto val, sf::Vector2f pos) :forms{ txtrs }
    {
        Button_Interface<Media_Button>::update_button(name, forms, val, pos);
    }

    auto operator()(Music_Player& mp)const& ->void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        Button_Interface<Media_Button>::display_manager(*this, target);
    }

    std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{ default_texture()
        ,default_texture(),default_texture() };

    Button_Names::Media name{};
    ButtonMode setting{};
};

class Game_State_Menu;

struct Game_State_Button : public Button
{
public:
    Game_State_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs
        , auto val, sf::Vector2f pos, std::string_view target_label) :forms{ txtrs }
    {
        Button_Interface<Game_State_Button>::update_button(name, forms, val, pos);
        label.setString(target_label);
        label.setFillColor({ 236,203,180 });

        label.setCharacterSize(22);
        label.setPosition({ pos.x, pos.y });
    }

    auto operator()(Game_State_Menu& gsm)const& ->void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        Button_Interface<Game_State_Button>::display_manager(*this, target);
        target.draw(label);
    }

    std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{ default_texture()
        ,default_texture(),default_texture() };

    sf::Text label{ Util::load_font() };
    Button_Names::Game_State name{};
    ButtonMode setting{};
};

class Exit_Menu;

struct Exit_Menu_Button : public Button
{
public:
    Exit_Menu_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs
        , auto val, sf::Vector2f pos, std::string_view target_label) :forms{ txtrs }
    {
        Button_Interface<Exit_Menu_Button>::update_button(name, forms, val, pos);
        label.setString(target_label);
        label.setFillColor({ 236,203,180 });

        label.setCharacterSize(22);
        label.setPosition({ pos.x, pos.y });
    }

    auto operator()(Exit_Menu& em)const& ->void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        Button_Interface<Game_State_Button>::display_manager(*this, target);
        target.draw(label);
    }

    std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{ default_texture()
    ,default_texture(),default_texture() };

    sf::Text label{ Util::load_font() };
    Button_Names::Game_State name{};
    ButtonMode setting{};
};

#endif //BUTTON_HPP