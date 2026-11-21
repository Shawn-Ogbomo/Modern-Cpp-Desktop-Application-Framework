#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include <span>
#include <SFML/Graphics.hpp>
#include "../include/state.hpp"
#include "../include/util.hpp"

class Caret : sf::Drawable
{
public:
    Caret()
    {
        indicator.setFillColor({ 21,73,120 });
        indicator.setCharacterSize(22);
        indicator.rotate(sf::degrees(-11.3f));
        indicator.setPosition({});
    }

    /// TODO: This should make the caret blink
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        ///Draw Indicator only if it is on
        ///Toggle it on an off every second
        /// sync it to local time in time status
    }
private:
    /// synced with time... to blink every second if text box is active and idle and can't exceed bounds of text field
    /// Advance the indicator past the size of the letter entered
    /// Decrement the indicator when pressing backspace and clear the length of the letter
    /// Indicator cant go past bounds of text field
    sf::Text indicator{ Util::load_font(), '|' };
    ButtonMode state{};
};

class Text_Field : sf::Drawable
{
    static constexpr auto character_limit = 3;
public:
    Text_Field() : field{ { 170,30 } }
    {
        field.setPosition({ 500,50 });
        field.setFillColor({ 236, 203, 180 });
        text.setPosition({ 500,50 });
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(field);
    }

    auto operator +=(char c) & -> void;
    auto operator -=(char c) & -> void;
private:
    Caret indicator;
    std::size_t pos{};
    sf::RectangleShape field;
    sf::Text text{ Util::load_font() };
    std::array<char, character_limit> buffer{};
};

struct Prompts
{
    std::array <std::string, 3> labels{
        "Are You\nSure?",
        "Log Win To\nDatabase?",
        "Enter Your Alias: "
    };
};

inline auto get_prompts() -> const Prompts&
{
    static const auto messages = Prompts{};
    return messages;
}

class Text_Box : sf::Drawable
{
public:
    Text_Box() = default;

    Text_Box(std::string_view text, sf::Sprite& tb
        , std::span<const sf::RenderWindow>rws);

    auto prompt() const& ->const sf::Text&;
    auto prompt() & ->sf::Text&;

    auto img() const& -> const sf::Sprite& { return internal_img.front(); }
    auto img() & -> sf::Sprite& { return internal_img.front(); }

    auto state() const& -> ButtonMode { return internal_state; }
    auto state() & ->ButtonMode& { return internal_state; }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    ButtonMode internal_state{};
    std::span<sf::Sprite> internal_img;

    std::optional<Text_Field> field;
    std::optional< sf::Text> internal_prompt;
};

#endif // TEXT_BOX_HPP