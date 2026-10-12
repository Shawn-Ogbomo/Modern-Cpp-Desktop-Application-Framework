#ifndef TIME_STATUS_HPP
#define TIME_STATUS_HPP

#include <string>

#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

#include"../include/util.hpp"

struct Time_Status : public sf::Drawable
{
public:
    Time_Status() = default;
    auto update(const sf::Clock& c) & -> void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Text date{ Util::load_font() };
    sf::Text elapsed_time{ Util::load_font() };

    std::string date_today;

    std::chrono::hours h{};
    std::chrono::minutes m{};
    std::chrono::seconds s{};
};

#endif // TIME_STATUS_HPP