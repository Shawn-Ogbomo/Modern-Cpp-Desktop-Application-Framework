#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../include/music_player.hpp"
#include "../include/state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"
    
class Button : public sf::Drawable
{
public:
    static const sf::Texture t;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
    virtual ~Button() = default;
};

class Media_Button : public Button
{
public:
    friend class Music_Player;

    Media_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs, int val, sf::Vector2f pos);

    auto operator()(Music_Player& mp)const & -> void;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {target.draw(std::get<0>(forms));}
private:
    std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{t,t,t};
    Button_Interface::Button_Names::Media name{};
};

class Game_State_Button : public Button
{
public:
    Game_State_Button(const std::tuple<sf::Texture, sf::Texture, sf::Texture>& txtrs, int val, sf::Vector2f pos);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(std::get<0>(forms)); }
private:
    std::tuple<sf::Sprite, sf::Sprite, sf::Sprite> forms{ t,t,t };
    Button_Interface::Button_Names::Media name{};
};

#endif //BUTTON_HPP