#include <ranges>

#include "../include/directory_manager.hpp"
#include "../include/music_player.hpp"
#include "../include/util.hpp"

using namespace std::chrono_literals;
namespace D_M = Directory_Manager;
namespace fs = std::filesystem;
namespace B_N = Button_Names;
namespace rng = std::ranges;

Music_Player::Music_Player()
{
    caption.setFillColor({ 236,203,180 });
    caption.setString("Song: ");
    caption.setCharacterSize(26);
    caption.setPosition({ 600, 842 });

    for (auto index = 0; const auto& song : fs::directory_iterator{ D_M::assets_dir()
        / "audio" }) [[likely]]
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

    for (auto internal_index = B_N::Media{}; const auto& texture : bm.textures) [[likely]]
    {
        buttons.push_back({ texture, internal_index, button_pos });
        ++internal_index;
        button_pos.x += 35;
    }

    mode = ButtonMode::on;
    operator()(B_N::Media::play);
}

void Music_Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(caption);
    target.draw(songs[current_song].first);
    rng::for_each(buttons, [&target](const auto& button) { [[likely]]
        target.draw(button);
        });
}

auto Music_Player::idle() & -> void
{
    if (const auto& done = songs[current_song].second; done.getPlayingOffset()
        >= done.getDuration() - 500000us) [[unlikely]]
    {
        operator()(B_N::Media::next);
    }
}

auto Music_Player::operator()(Button_Names::Media name) & ->void
{
    switch (name)
    {
    case B_N::Media::prev:
        stop();
        prev();
        play();
        break;
    case B_N::Media::pause:
        pause();
        break;
    case B_N::Media::play:
        play();
        break;
    case B_N::Media::next:
        stop();
        next();
        play();
        break;
    case B_N::Media::stop:
        stop();
        break;
    }
}