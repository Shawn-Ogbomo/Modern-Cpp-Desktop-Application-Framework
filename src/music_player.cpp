#include <ranges>

#include "../include/directory_manager.hpp"
#include "../include/music_player.hpp"
#include "../include/util.hpp"

using namespace std::chrono_literals;
namespace D_M = Directory_Manager;
namespace fs = std::filesystem;
namespace rng = std::ranges;

Music_Player::Music_Player()
{
    caption.setFillColor({ 236,203,180 });
    caption.setString("Song: ");
    caption.setCharacterSize(26);
    caption.setPosition({ 600, 842 });

    for (auto index = 0; const auto& song : fs::directory_iterator{ D_M::assets_dir()
        / "audio" })
    {
        songs.emplace_back(sf::Text{ Util::load_font(), song.path().filename().stem().string() }, song);

        auto& [name, file] = songs[index];

        name.setFillColor({ 236,203,180 });
        name.setPosition({ 674, 842 });
        name.setCharacterSize(26);

        ++index;
    }

    limit = songs.size();

    bm.load_textures();

    buttons.reserve(bm.textures.size());

    auto button_pos = sf::Vector2f{ 452.0f - 35.0f, 842.0f };

    for (auto internal_index = Button_Names::Media{}; const auto& texture : bm.textures)
    {
        buttons.push_back({ texture, internal_index, button_pos });
        ++internal_index;
        button_pos.x += 35;
    }

    mode = ButtonMode::on;
    const auto& play = buttons[static_cast<int>((Button_Names::Media::play))];
    play.operator()(*this);
}

auto Music_Player::click_listener(sf::Vector2f cursor_pos) & -> void
{
    Button_Interface<Media_Button>::click_listener(std::span{ buttons }, cursor_pos);
}

auto Music_Player::release_listener(sf::Vector2f cursor_pos) & ->void
{
    Button_Interface<Media_Button>::release_listener(*this, cursor_pos);
}

void Music_Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(caption);
    target.draw(songs[current_song].first);
    rng::for_each(buttons, [&target](const auto& button) {
        target.draw(button);
        });
}

auto Music_Player::idle() & -> void
{
    if (const auto& done = songs[current_song].second; done.getPlayingOffset()
        >= done.getDuration() - 500000us)
    {
        const auto& next = buttons[static_cast<int>(Button_Names::Media::next)];
        next.operator()(*this);
    }
}