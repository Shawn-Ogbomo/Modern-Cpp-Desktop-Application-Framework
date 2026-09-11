#ifndef TIME_STATUS_HPP
#define TIME_STATUS_HPP

#include <string>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../include/directory_manager.hpp"
#include "../include/state.hpp"
#include"../include/util.hpp"

class Time_Status : public sf::Drawable
{
public:
    Time_Status();
    auto update(sf::Clock& c, Game_State gs) & -> void;
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Text date{ Util::load_font(std::filesystem::path{ Directory_Manager::assets_dir()
        / "fonts" / "galafera-med-font" / "GalaferaMediumItalic-JpXJK.ttf" }) };

    sf::Text elapsed_time{ Util::load_font(std::filesystem::path{ Directory_Manager::assets_dir()
        / "fonts" / "galafera-med-font" / "GalaferaMediumItalic-JpXJK.ttf" }) };

    std::string date_today;

    std::chrono::hours h{};
    std::chrono::minutes m{};
    std::chrono::seconds s{};
};

#endif // TIME_STATUS_HPP