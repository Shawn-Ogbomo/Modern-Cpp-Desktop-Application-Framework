#ifndef MUSIC_PLAYER_HPP
#define MUSIC_PLAYER_HPP

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

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

    Media_Button(const Texture_Forms& txtrs, Button_Names::Media val
        , sf::Vector2f pos) : forms{ txtrs }
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

struct Track_Title
{
    Track_Title() = default;
    Track_Title(std::string s) :name{ Util::load_font(),std::move(s) } {}
    Track_Title(Track_Title&&) = default;
    auto operator =(Track_Title&&) noexcept -> Track_Title & = default;
    sf::Text name{ Util::load_font() };
};

class  Music_Player : public sf::Drawable
{
    static constexpr auto song_limit = 10;
    using Media_Buttons = std::array<Media_Button, Media_Button::limit>;
public:
    Music_Player(const Button_Manager& bm);
    Music_Player(Music_Player&&) = default;

    auto operator =(Music_Player&&) noexcept -> Music_Player & = default;
    operator bool() const& { return static_cast<bool>(mode); }
    auto operator()(Button_Names::Media name) & ->void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    auto idle() & -> void;
    auto buttons() & -> Media_Buttons& { return internal_buttons; }
    auto state() & -> ButtonMode& { return mode; };
    auto clicked_button() & -> std::span<Media_Button>& { return mbs; }
private:
    sf::Text caption{ Util::load_font() };
    std::size_t current_song{};

    std::unique_ptr<sf::Music[]> songs;

    std::unique_ptr<Track_Title[]> song_names;
    Media_Buttons internal_buttons{};

    ButtonMode mode{};

    std::span<Media_Button> mbs;
};

#endif // MUSIC_PLAYER_HPP