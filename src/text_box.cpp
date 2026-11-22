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

Text_Box::Text_Box(std::string_view text, sf::Sprite& tb
    , std::span<const sf::RenderWindow>rws
    , std::optional<sf::RectangleShape> ors) : internal_img{ &tb,1 }
    , internal_field{std::move(ors)}
{
    const auto dimensions_window = static_cast<sf::Vector2f>(rws.front().getSize());
    const auto dimensions_textbox = sf::Vector2f{ internal_img.front().getGlobalBounds().size };

    internal_prompt.setString(text);
    internal_prompt.setCharacterSize(26);
    internal_prompt.setFillColor({ 236,203,180 });

    const auto dimensions_prompt = internal_prompt.getGlobalBounds().size;

    internal_prompt.setPosition({ ((dimensions_window.x - dimensions_textbox.x) / 2)
        + (dimensions_textbox.x / 2)- (dimensions_prompt.x / 2) 
        , ((dimensions_window.y - dimensions_textbox.y) / 2)
        + (dimensions_textbox.y / 2) - dimensions_prompt.y });

    internal_img.front().setPosition({ (dimensions_window.x - dimensions_textbox.x) / 2
        , (dimensions_window.y - dimensions_textbox.y) / 2 });
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

    if (internal_field)
    {
        target.draw(*internal_field);
    }
}