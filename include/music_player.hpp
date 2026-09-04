#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

#include "../include/button.hpp"
#include "../include/state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

class Media_Button; 

class  Music_Player : public sf::Drawable
{
    sf::Font font;
public:

    Music_Player();
    Music_Player(Music_Player&&) noexcept = default;
    //use reference qualifiers with assignment operators as well...
    auto operator =(Music_Player&&) noexcept -> Music_Player&;
    auto operator()(sf::RenderWindow& rw, sf::Vector2f cursor_pos = {}) & ->void;
    operator bool() const& { return static_cast<bool>(mode); };

    auto next() & -> void { current_song = current_song < limit - 1 ? ++current_song : 0; };
    auto prev() & -> void { current_song = current_song > 0 ? --current_song : current_song = limit - 1; };
    auto stop() & -> void { songs[current_song].second.stop(); };
    auto pause() & -> void { songs[current_song].second.pause(); };
    auto play() & -> void { songs[current_song].second.play(); };
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    auto idle(Music_Player& mp) & -> void;

    sf::Text caption{ font };
    std::size_t limit{};
    std::size_t current_song{};
    std::vector<std::pair<sf::Text, sf::Music>> songs;
    std::vector<Media_Button> buttons;
    Button_Manager bm;
    Button_Interface::ButtonMode mode{};
};

#endif // MUSIC_PLAYER_HPP