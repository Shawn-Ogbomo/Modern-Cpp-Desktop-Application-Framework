#include "../include/text_box.hpp"

auto Text_Field::operator +=(char c) & -> void
{
    if (pos != buffer.size())
    {
        buffer[pos] += c;
        text.setString(buffer[pos]);
        ++pos;
    }
}

/// TODO: The caret needs to blink while clearing characters
auto Text_Field::operator -=(char c) & -> void
{
    char backspace = 8;

    if (c == backspace)
    {
        if (!pos)
        {
            buffer[pos] = char{};
            text.setString(buffer[pos]);
            return;
        }

        buffer[pos] = char{};
        text.setString(buffer[pos]);
        --pos;
    }
}

auto configure_text_box(std::string_view text, const sf::RenderWindow& rws
    , sf::Sprite& img, sf::Text& prompt, sf::Vector2f offset = {}) -> void
{
    const auto dimensions_window = static_cast<sf::Vector2f>(rws.getSize());
    const auto dimensions_textbox = sf::Vector2f{ img.getGlobalBounds().size };

    prompt.setString(text);
    prompt.setCharacterSize(26);
    prompt.setFillColor({ 236,203,180 });

    const auto dimensions_prompt = prompt.getGlobalBounds().size;

    prompt.setPosition({ (((dimensions_window.x - dimensions_textbox.x) / 2)
        + (dimensions_textbox.x / 2) - (dimensions_prompt.x / 2)) + offset.x
        , ((dimensions_window.y - dimensions_textbox.y) / 2)
        + (dimensions_textbox.y / 2) - dimensions_prompt.y + offset.y });

    img.setPosition({ (dimensions_window.x - dimensions_textbox.x) / 2
        , (dimensions_window.y - dimensions_textbox.y) / 2 });
}

Text_Box::Text_Box(std::string_view text, sf::Sprite& tb
    , const sf::RenderWindow& rws) : internal_img{ &tb,1 }
{
    configure_text_box(text, rws, internal_img.front()
        , internal_prompt);
}

auto Text_Box::prompt() const& ->const sf::Text&
{
    return internal_prompt;
}

auto Text_Box::prompt() & ->sf::Text&
{
    return internal_prompt;
}

void Text_Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(internal_img.front());
    target.draw(internal_prompt);
}

Input_Box::Input_Box(std::string_view text, sf::Sprite& tb
    , const sf::RenderWindow& rws
    , sf::RectangleShape rs) : internal_field{ std::move(rs) }, internal_img{ &tb,1 }
{
    configure_text_box(text, rws, internal_img.front()
        , internal_prompt, { 0,-30 });
}

auto Input_Box::prompt() const& ->const sf::Text&
{
    return internal_prompt;
}

auto Input_Box::prompt() & ->sf::Text&
{
    return internal_prompt;
}

void Input_Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(internal_img.front());
    target.draw(internal_prompt);
    target.draw(internal_field);
}