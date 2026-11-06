#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <memory>

#include "../include/button.hpp"
#include "../include/directory_manager.hpp"
#include "../include/state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/refs.hpp"
#include "../include/util.hpp"

struct Media_Button;

struct  Music_Player : public sf::Drawable
{
    static constexpr auto limit = 10;
public:
    Music_Player();

    operator bool() const& { return static_cast<bool>(mode); };

    auto operator()(Button_Names::Media name) & ->void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    auto idle() & -> void;
    auto next() & -> void { current_song = current_song < limit - 1 ? ++current_song : 0; };
    auto prev() & -> void { current_song = current_song > 0 ? --current_song : current_song = limit - 1; };
    auto stop() & -> void { songs[current_song].stop(); };
    auto pause() & -> void { songs[current_song].pause(); };
    auto play() & -> void { songs[current_song].play(); };

    sf::Text caption{ Util::load_font() };

    std::size_t current_song{};

    std::unique_ptr<sf::Music[]> songs;
    
    std::vector<sf::Text> song_names;
    std::vector<Media_Button> buttons;

    Button_Manager bm;
    ButtonMode mode{};
    std::span<Media_Button> mbs;
};

#endif // MUSIC_PLAYER_HPP