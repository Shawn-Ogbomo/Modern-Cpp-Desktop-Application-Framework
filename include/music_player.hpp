#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <array>
#include <memory>

#include "../include/button.hpp"
#include "../include/directory_manager.hpp"
#include "../include/state.hpp"
#include "../include/texture_manager.hpp"
#include "../include/util.hpp"

struct Media_Button : public Button
{
    static constexpr auto limit = 5;

    Media_Button() = default;

    Media_Button(const Texture_Forms& txtrs, auto val, sf::Vector2f pos) : forms{ txtrs }
    {
        update_button(contents.name, forms, val, pos);
    }

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
    {
        display_manager(*this, target);
    }

    Forms forms;
    Properties<Button_Names::Media> contents;
};

struct  Music_Player : public sf::Drawable
{
    static constexpr auto song_limit = 10;

    Music_Player();
    Music_Player(Music_Player&&) = default;

    auto operator =(Music_Player&&) noexcept -> Music_Player & = default;
    operator bool() const& { return static_cast<bool>(mode); };
    auto operator()(Button_Names::Media name) & ->void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    auto idle() & -> void;
    auto next() & -> void { current_song = current_song < song_limit - 1 ? ++current_song : 0; };
    auto prev() & -> void { current_song = current_song > 0 ? --current_song : current_song = song_limit - 1; };
    auto stop() const & -> void { songs[current_song].stop(); };
    auto pause() const & -> void { songs[current_song].pause(); };
    auto play() const & -> void { songs[current_song].play(); };

    sf::Text caption{ Util::load_font() };
    std::size_t current_song{};

    std::unique_ptr<sf::Music[]> songs;

    std::vector<sf::Text> song_names; 
    std::array<Media_Button,Media_Button::limit> buttons{};

    Button_Manager bm;
    ButtonMode mode{};
    std::span<Media_Button> mbs;
};

#endif // MUSIC_PLAYER_HPP