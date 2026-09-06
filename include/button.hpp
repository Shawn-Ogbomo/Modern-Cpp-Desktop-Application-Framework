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
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual const std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& states() const & = 0;
    virtual ~Button() = default;

    template <typename T, typename T2>
    static auto operator()(const std::vector<T>& buttons, T2& obj, sf::Vector2f cursor_pos, sf::RenderWindow& rw) -> void
    {
        const auto button = std::ranges::find_if(buttons, [&](const auto& b) {
            return std::get<0>(b.states()).getGlobalBounds().contains(cursor_pos);
            });

        if (button != std::end(buttons))
        {
            const auto& states_ref = button->states();

            rw.draw(std::get<1>(states_ref));
            rw.display();

            while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                rw.draw(std::get<2>(states_ref));
                rw.display();
            }

            if (const auto cursor_pos_released = static_cast<sf::Vector2f>(sf::Mouse::getPosition(rw));
                std::get<0>(button->states()).getGlobalBounds().contains(cursor_pos_released))
            {
                rw.draw(std::get<1>(states_ref));
                rw.display();

                rw.draw(std::get<0>(states_ref));
                rw.display();
                button->operator()(obj);
                return;
            }
        }
    }
};

///TODO: Write a concept to make this exclusive to enums, namely, your button enum for compile-time safety.
template <typename T>
auto update_button(T& internal_name, std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& forms, T val, sf::Vector2f pos) -> void
{
    internal_name = val;

    auto& [form_1, form_2, form_3] = forms;

    form_1.setPosition(pos);
    form_2.setPosition(pos);
    form_3.setPosition(pos);
}

class Music_Player;

class Media_Button : public Button
{
public:
    template <typename T>
        Media_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs, T val, sf::Vector2f pos)
        :forms{ txtrs }{update_button(name, forms, val, pos);}

    auto operator()(Music_Player& mp)const & -> void;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {target.draw(std::get<0>(forms));}
    const std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& states()  const & override { return forms; }
    const Button_Interface::Button_Names::Media& type() const & { return name; }
private:
    std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{t,t,t};
    Button_Interface::Button_Names::Media name{};
};

class  Game_State_Button : public Button
{
public:
    template <typename T>
   Game_State_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs, T val, sf::Vector2f pos)
        :forms{ txtrs } {  update_button(name, forms, val, pos);}

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(std::get<0>(forms)); }
    const std::tuple<sf::Sprite, sf::Sprite, sf::Sprite>& states()  const & override { return forms; }
    const Button_Interface::Button_Names::Status& type() const & { return name; }
private:
    std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{ t,t,t };
    Button_Interface::Button_Names::Status name{};
};

#endif //BUTTON_HPP