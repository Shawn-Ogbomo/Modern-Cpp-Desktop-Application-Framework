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

struct Track_Title
{
    Track_Title() = default;
    Track_Title(std::string s) :name{ Util::load_font(),std::move(s) } {}
    Track_Title(Track_Title&&) = default;
    auto operator =(Track_Title&&) noexcept -> Track_Title & = default;
    sf::Text name{ Util::load_font() };
};

using MB = Button <Button_Names::Media>;

class  Music_Player : public sf::Drawable
{
    static constexpr auto song_limit = 10;
    static constexpr auto button_limit = 5;

    using Media_Buttons = std::array<MB, button_limit>;
    using M_P = Menu_Properties<Media_Buttons, MB>;
public:
    Music_Player(const Button_Manager& bm);
    Music_Player(Music_Player&&) = default;

    auto operator =(Music_Player&&) noexcept -> Music_Player & = default;
    operator bool() const& { return static_cast<bool>(menu_properties.mode); }
    auto operator()(Button_Names::Media name) & ->void;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    auto idle() & -> void;
    auto buttons() & -> Media_Buttons& { return menu_properties.state_buttons; }
    auto state() & -> ButtonMode& { return menu_properties.mode; };
    auto clicked_button() & -> std::span<MB>& { return menu_properties.spn; }
private:
    sf::Text caption{ Util::load_font() };
    std::size_t current_song{};

    std::unique_ptr<sf::Music[]> songs;
    std::unique_ptr<Track_Title[]> song_names;

    M_P menu_properties{ ButtonMode::on };
};

#endif // MUSIC_PLAYER_HPP