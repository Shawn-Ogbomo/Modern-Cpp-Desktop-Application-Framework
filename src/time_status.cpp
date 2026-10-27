#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "../include/time_status.hpp"
#include "../include/util.hpp"

namespace chr = std::chrono;

auto Time_Status::update(const sf::Clock& c) & -> void
{
    auto elapsed = sf::Time{ chr::microseconds(c.getElapsedTime()) };

    h = chr::duration_cast<chr::hours>(static_cast<chr::microseconds>(elapsed));
    elapsed -= h;

    m = chr::duration_cast<chr::minutes>(static_cast<chr::microseconds>(elapsed));
    elapsed -= m;

    s = chr::duration_cast<chr::seconds>(static_cast<chr::microseconds>(elapsed));

    elapsed_time.setString("Elapsed Time: " + std::to_string(h.count()) + " hours: " + std::to_string(m.count())
        + " minutes: " + std::to_string(s.count()) + " seconds");

    date.setString("Date: " + Util::local_time());
}

Time_Status::Time_Status()
{
    elapsed_time.setCharacterSize(26);
    elapsed_time.setPosition({ 0, 871 });
    elapsed_time.setFillColor({ 236,203,180 });

    date.setCharacterSize(26);
    date.setPosition({ 600, 871 });
    date.setFillColor({ 236,203,180 });
}

void Time_Status::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(date);
    target.draw(elapsed_time);
}