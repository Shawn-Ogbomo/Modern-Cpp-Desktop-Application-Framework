#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Transformable.hpp>

#include "../include/time_status.hpp"
#include "../include/util.hpp"

auto Time_Status::update(sf::Clock& c, Game_State gs) & -> void
{
    auto t0 = std::chrono::steady_clock::now();
    if (gs != Game_State::playing)
    {
        c.stop();
    }

    else if (gs == Game_State::playing)
    {
        c.start();

        auto elapsed = sf::Time{ std::chrono::microseconds(c.getElapsedTime()) };

        h = std::chrono::duration_cast<std::chrono::hours>(static_cast<std::chrono::microseconds>(elapsed));
        elapsed -= h;

        m = std::chrono::duration_cast<std::chrono::minutes>(static_cast<std::chrono::microseconds>(elapsed));
        elapsed -= m;

        s = std::chrono::duration_cast<std::chrono::seconds>(static_cast<std::chrono::microseconds>(elapsed));

        elapsed_time.setString("Elapsed Time: " + std::to_string(h.count()) + " hours: " + std::to_string(m.count())
            + " minutes: " + std::to_string(s.count()) + " seconds");
    }

    date.setString(("Date: " + Util::local_time()));
    auto t1 = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::milli> d{ t1 - t0 };
    std::cout << d.count() << "ms\n";
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