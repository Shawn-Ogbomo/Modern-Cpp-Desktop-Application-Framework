#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include <SFML/System/Clock.hpp>

#include <span>
#include <SFML/Graphics.hpp>

#include "../include/state.hpp"
#include "../include/util.hpp"

namespace
{
    constexpr auto character_limit = 3;
    constexpr auto caret_start_pos = sf::Vector2f{ 425.0f, 440.0f };
    constexpr auto cerulean_blue = sf::Color{ 21,73,120 };
    constexpr auto peach_beige = sf::Color{ 236,203,180 };
};

class Caret : public sf::Drawable
{
public:
    Caret()
    {
        internal_clock.stop();
        indicator.setCharacterSize(22);
        indicator.setPosition(caret_start_pos);
        indicator.setFillColor(cerulean_blue);
        indicator.rotate(sf::degrees(-11.3f));
    }

    auto idle() & -> void;
    auto timer() & ->sf::Clock& { return internal_clock; }
    auto symbol() & -> sf::Text& { return indicator; };

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(indicator);
    }
private:
    sf::Clock internal_clock;
    ButtonMode state{};
    sf::Text indicator{ Util::load_font(), '|' };
};

class Text_Field : public sf::Drawable
{
public:
    Text_Field() = default;

    Text_Field(sf::RectangleShape) : field{ { 170,30 } }
    {
        field.setPosition({ caret_start_pos });
        field.setFillColor(peach_beige);
        text.setPosition({ caret_start_pos });
        text.setCharacterSize(26);
        text.setFillColor(cerulean_blue);
    }

    auto caret() & -> Caret& { return internal_caret; }
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        target.draw(field);
        target.draw(internal_caret);
        target.draw(text);
    }

    auto operator +=(sf::Keyboard::Scancode c) & -> void;
    auto operator -=(sf::Keyboard::Scancode) & -> void;
private:
    Caret internal_caret;
    std::size_t pos{};
    sf::RectangleShape field;
    sf::Text text{ Util::load_font() };
    std::string buffer;
};

struct Prompts
{
    std::array <std::string, character_limit> labels{
        "Are You\nSure?",
        "Log Win To\nDatabase?",
        "Enter Alias:"
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
        , const sf::RenderWindow& rws);

    operator bool()const& { return static_cast<bool>(internal_state); }

    auto prompt() const& ->const sf::Text&;
    auto prompt() & ->sf::Text&;

    auto img() const& -> const sf::Sprite& { return internal_img.front(); }
    auto img() & -> sf::Sprite& { return internal_img.front(); }

    auto state() & ->ButtonMode& { return internal_state; }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    ButtonMode internal_state{};
    std::span<sf::Sprite> internal_img;
    sf::Text internal_prompt{ Util::load_font() };
};

class Input_Box : public sf::Drawable
{
public:
    Input_Box() = default;

    Input_Box(std::string_view text, sf::Sprite& tb
        , const sf::RenderWindow& rws
        , sf::RectangleShape rs);

    operator bool()const& { return static_cast<bool>(internal_state); }

    auto prompt() const& ->const sf::Text&;
    auto prompt() & ->sf::Text&;

    auto img() const& -> const sf::Sprite& { return internal_img.front(); }
    auto img() & -> sf::Sprite& { return internal_img.front(); }

    auto state() & ->ButtonMode& { return internal_state; }

    auto field() & ->Text_Field& { return internal_field; }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    ButtonMode internal_state{};
    std::span<sf::Sprite> internal_img;
    Text_Field internal_field;
    sf::Text internal_prompt{ Util::load_font() };
};

#endif // TEXT_BOX_HPP