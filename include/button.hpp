#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../include/music_player.hpp"
#include "../include/state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

struct Button : public sf::Drawable
{
public:
    static const sf::Texture t;

    virtual operator bool() const& = 0;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual const std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& states() const& = 0;
    virtual Button_Interface::ButtonMode& mode() & = 0;
    virtual ~Button() = default;

    static auto click_listener(auto& buttons, sf::Vector2f cursor_pos) -> void
    {
        const auto button = std::ranges::find_if(buttons, [&](const auto& b) {
            return std::get<0>(b.states()).getGlobalBounds().contains(cursor_pos);
            });

        if (button != std::end(buttons))
        {
            button->mode() = Button_Interface::ButtonMode::on;
        }
    }

    /// TODO: This function does not fulfill its intent.
    static auto release_listener(auto& buttons, auto& obj, sf::Vector2f cursor_pos) -> void
    {
        auto button = std::ranges::find_if(buttons, [&](auto& b) {
            return std::get<0>(b.states()).getGlobalBounds().contains(cursor_pos) && b.mode() == Button_Interface::ButtonMode::on;
            });

        if (button != std::end(buttons) && *button)
        {
            button->mode() = Button_Interface::ButtonMode::off;
            button->operator()(obj);
        }
    }
};

///TODO: Write a concept to make this exclusive to enums, namely, your button enum for compile-time safety.
auto update_button(auto& internal_name, std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& forms, auto val, sf::Vector2f pos) -> void
{
    internal_name = val;

    auto& [form_1, form_2, form_3] = forms;

    form_1.setPosition(pos);
    form_2.setPosition(pos);
    form_3.setPosition(pos);
}

auto display_manager(const auto& button, sf::RenderTarget& target) -> void
{
    button ? target.draw(std::get<2>(button.states())) : target.draw(std::get<0>(button.states()));
}

class Music_Player;

class Media_Button : public Button
{
public:
    Media_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs, auto val, sf::Vector2f pos)
        :forms{ txtrs }
    {
        update_button(name, forms, val, pos);
    }

    operator bool() const& override { return static_cast<int>(setting); }
    auto operator()(Music_Player& mp)const& -> void;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override { display_manager(*this, target); }
    const std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& states()  const& override { return forms; }
    const Button_Interface::Button_Names::Media& type() const& { return name; }
    Button_Interface::ButtonMode& mode() & override { return setting; }
private:
    std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{ t,t,t };
    Button_Interface::Button_Names::Media name{};
    Button_Interface::ButtonMode setting{};
};

class  Game_State_Button : public Button
{
public:
    Game_State_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs, auto val, sf::Vector2f pos)
        :forms{ txtrs }
    {
        update_button(name, forms, val, pos);
    }
    operator bool() const& override { return static_cast<int>(setting); }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override { display_manager(*this, target); }
    const std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& states()  const& override { return forms; }
    const Button_Interface::Button_Names::Status& type() const& { return name; }
    Button_Interface::ButtonMode& mode() & override { return setting; }
private:
    std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{ t,t,t };
    Button_Interface::Button_Names::Status name{};
    Button_Interface::ButtonMode setting{};
};

#endif //BUTTON_HPP