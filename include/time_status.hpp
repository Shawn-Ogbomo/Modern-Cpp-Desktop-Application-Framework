#ifndef TIME_STATUS_HPP
#define TIME_STATUS_HPP

#include <string>

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

#include"../include/util.hpp"

struct Time_Status : public sf::Drawable
{
    Time_Status();
    auto update(const sf::Clock& c) & -> void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Text date{ Util::load_font() };
    sf::Text elapsed_time{ Util::load_font() };
    std::string date_today;
};

#endif // TIME_STATUS_HPP