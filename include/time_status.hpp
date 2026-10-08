#ifndef TIME_STATUS_HPP
#define TIME_STATUS_HPP

#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>

#include "../include/directory_manager.hpp"
#include "../include/state.hpp"
#include"../include/util.hpp"

class Time_Status : public sf::Drawable
{
public:
    Time_Status();
    auto set_clock(std::shared_ptr<sf::Clock>shrptr_c) & -> void { c_sp_ts = shrptr_c; }
    auto update() & -> void;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Text date{ Util::load_font() };
    sf::Text elapsed_time{ Util::load_font() };

    std::string date_today;

    std::chrono::hours h{};
    std::chrono::minutes m{};
    std::chrono::seconds s{};

    std::shared_ptr<sf::Clock> c_sp_ts;
};

#endif // TIME_STATUS_HPP