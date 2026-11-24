#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include <span>
#include <SFML/Graphics.hpp>
#include "../include/state.hpp"
#include "../include/util.hpp"

class Caret : public sf::Drawable
{
public:
    Caret()
    {
        indicator.setCharacterSize(22);
        indicator.setPosition({ 425,440});
        indicator.setFillColor({ 21,73,120 });
        indicator.rotate(sf::degrees(-11.3f));
    }

    /// TODO: This should make the caret blink
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(indicator);
        ///Draw Indicator only if it is on
        ///Toggle it on an off every second
        /// sync it to local time in time status
    }
private:
    /// synced with time... to blink every second if text box is active and idle
    /// Advance the indicator past the size of the character entered
    /// Decrement the indicator when pressing backspace and clear the length of the letter
    /// Indicator cant go past bounds of text field
    sf::Text indicator{ Util::load_font(), '|' };
    ButtonMode state{};
};

class Text_Field : public sf::Drawable
{
public:
    Text_Field(sf::RectangleShape) : field{ { 170,30 } }
    {
        field.setPosition({ 425,440 });
        field.setFillColor({ 236, 203, 180 });
        text.setPosition({ 500,50 });
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(field);
        target.draw(caret);
    }

    auto operator +=(char c) & -> void;
    auto operator -=(char c) & -> void;
private:
    Caret caret;
    std::size_t pos{};
    sf::RectangleShape field;
    sf::Text text{ Util::load_font() };
    std::array<char, limit+1> buffer{};
};

struct Prompts
{
    std::array <std::string, limit+1> labels{
        "Are You\nSure?",
        "Log Win To\nDatabase?",
        "Enter Name:"
    };
};

inline auto get_prompts() -> const Prompts&
{
    static const auto messages = Prompts{};
    return messages;
}

class Text_Box : public sf::Drawable
{
public:
    Text_Box() = default;

    Text_Box(std::string_view text, sf::Sprite& tb
        , std::span<const sf::RenderWindow>rws
        , std::optional<sf::RectangleShape> ors);

    operator bool()const& { return static_cast<bool>(internal_state); }

    auto prompt() const& ->const sf::Text&;
    auto prompt() & ->sf::Text&;

    auto img() const& -> const sf::Sprite& { return internal_img.front(); }
    auto img() & -> sf::Sprite& { return internal_img.front(); }

    auto state() & ->ButtonMode& { return internal_state; }

    auto field() const& ->std::optional<Text_Field> { return internal_field; }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    ButtonMode internal_state{};
    std::span<sf::Sprite> internal_img;
    std::optional<Text_Field> internal_field;
    sf::Text internal_prompt{ Util::load_font() };
};

#endif // TEXT_BOX_HPP