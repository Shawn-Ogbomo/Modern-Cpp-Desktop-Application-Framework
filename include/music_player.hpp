#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <vector>

#include "../include/button.hpp"
#include "../include/directory_manager.hpp"
#include "../include/state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

struct Media_Button;

struct  Music_Player : public sf::Drawable
{
public:
    Music_Player();

    operator bool() const& { return static_cast<bool>(mode); };

    auto operator()(Button_Names::Media name) & ->void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    auto click_listener(sf::Vector2f cursor_pos) & -> void;
    auto release_listener(sf::Vector2f cursor_pos) & -> void;

    auto idle() & -> void;
    auto next() & -> void { current_song = current_song < limit - 1 ? ++current_song : 0; };
    auto prev() & -> void { current_song = current_song > 0 ? --current_song : current_song = limit - 1; };
    auto stop() & -> void { songs[current_song].second.stop(); };
    auto pause() & -> void { songs[current_song].second.pause(); };
    auto play() & -> void { songs[current_song].second.play(); };

    sf::Text caption{ Util::load_font() };

    std::size_t limit{};
    std::size_t current_song{};

    std::vector<std::pair<sf::Text, sf::Music>> songs;
    std::vector<Media_Button> buttons;

    Button_Manager bm;
    ButtonMode mode{};
    std::span<Media_Button> mbs;
};

#endif // MUSIC_PLAYER_HPP