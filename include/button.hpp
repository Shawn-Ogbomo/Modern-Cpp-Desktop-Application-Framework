#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../include/music_player.hpp"
#include "../include/state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

class Music_Player;

struct Button : public sf::Drawable
{
public:
    static const sf::Texture t;

    virtual operator bool() const& = 0;
    virtual ~Button() = default;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual const std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& states() const& = 0;
    virtual ButtonMode& mode() & = 0;
};

template <typename T>
class Button_Interface
{
public:
    static auto operator()(auto t1, auto& t2) ->void { t1->operator()(t2); }

    static auto click_listener(auto& buttons, sf::Vector2f cursor_pos) -> void
    {
        const auto button = std::ranges::find_if(buttons, [&](const auto& b) {
            return std::get<0>(b.states()).getGlobalBounds().contains(cursor_pos);
            });

        if (button != std::end(buttons))
        {
            button->mode() = ButtonMode::on;
            ob = &(*button);
        }
    }

    static auto release_listener(auto& obj, sf::Vector2f cursor_pos) -> void
    {
        if (ob)
        {
            if (std::get<0>((*ob)->states()).getGlobalBounds().contains(cursor_pos))
            {
                operator()(*ob, obj);
            }

            ob.value()->mode() = ButtonMode::off;
            ob = std::nullopt;
        }
    }

    ///TODO: Write a concept to make this exclusive to enums, namely, your button enum for compile-time safety.
    static auto update_button(auto& internal_name, std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& forms, auto val, sf::Vector2f pos) -> void
    {
        internal_name = val;

        auto& [form_1, form_2, form_3] = forms;

        form_1.setPosition(pos);
        form_2.setPosition(pos);
        form_3.setPosition(pos);
    }

    static auto display_manager(const auto& button, sf::RenderTarget& target) -> void
    {
        button ? target.draw(std::get<2>(button.states())) : target.draw(std::get<0>(button.states()));
    }
private:
    static inline std::optional<T*> ob;
};

class Media_Button : public Button
{
public:
    Media_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs, auto val, sf::Vector2f pos)
        :forms{ txtrs }
    {
        Button_Interface<Media_Button>::update_button(name, forms, val, pos);
    }

    operator bool() const& override { return static_cast<int>(setting); }
    auto operator()(Music_Player& mp)const& ->void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        Button_Interface<Media_Button>::display_manager(*this, target);
    }

    const std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& states()  const& override { return forms; }
    const Button_Names::Media& type() const& { return name; }
    ButtonMode& mode() & override { return setting; }
private:
    std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{ t,t,t };
    Button_Names::Media name{};
    ButtonMode setting{};
};

class  Game_State_Button : public Button
{
public:
    Game_State_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs, auto val, sf::Vector2f pos)
        :forms{ txtrs }
    {
        Button_Interface<Game_State_Button>::update_button(name, forms, val, pos);
    }

    operator bool() const& override { return static_cast<int>(setting); }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        Button_Interface<Game_State_Button>::display_manager(*this, target);
    }

    const std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& states()  const& override { return forms; }
    const Button_Names::Status& type() const& { return name; }
    ButtonMode& mode() & override { return setting; }
private:
    std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{ t,t,t };
    Button_Names::Status name{};
    ButtonMode setting{};
};

#endif //BUTTON_HPP