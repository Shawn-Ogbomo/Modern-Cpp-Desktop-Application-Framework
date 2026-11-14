#include "../include/directory_manager.hpp"
#include "../include/music_player.hpp"

using namespace std::chrono_literals;
namespace D_M = Directory_Manager;
namespace fs = std::filesystem;
namespace B_N = Button_Names;
namespace rng = std::ranges;
using namespace std::string_literals;

Music_Player::Music_Player() : songs{ std::make_unique <sf::Music[]>(song_limit)}
, song_names{std::make_unique<Track_Title[]>(song_limit)}
{
    caption.setString("Song: ");
    caption.setCharacterSize(26);
    caption.setPosition({ 600, 842 });
    caption.setFillColor({ 236,203,180 });

    for (auto index = 0; const auto& song : fs::directory_iterator{ D_M::assets_dir() / "audio" })
    {
        song_names[index] = {song.path().filename().stem().string() };
        songs[index] = sf::Music{ song };

        song_names[index].name.setCharacterSize(26);
        song_names[index].name.setPosition({ 674, 842 });
        song_names[index].name.setFillColor({ 236,203,180 });

        ++index;
    }

    bm.load_textures();

    auto button_pos = sf::Vector2f{ 452.0f - 35.0f, 842.0f };

    for (auto internal_index = B_N::Media{}; const auto& texture : bm.textures)
    {
        internal_buttons[static_cast<int>(internal_index)] 
            = {texture, internal_index, button_pos};
        
        ++internal_index;
        button_pos.x += 35;
    }

    mode = ButtonMode::on;
    operator()(B_N::Media::play);
}

void Music_Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(caption);
    target.draw(song_names[current_song].name);
    rng::for_each(internal_buttons, [&target](const auto& button) { 
        target.draw(button);
        });
}

auto Music_Player::idle() & -> void
{
    if (const auto& done = songs[current_song]; done.getPlayingOffset()
        >= done.getDuration() - 500000us) [[unlikely]]
    {
        operator()(B_N::Media::next);
    }
}

auto Music_Player::operator()(Button_Names::Media name) & ->void
{
    const auto& stop = [&,this]{ songs[current_song].stop(); };
    const auto& play = [&,this] { songs[current_song].play(); };
    const auto& pause = [&, this] { songs[current_song].pause(); };
    const auto& next = [&, this] { current_song = (current_song < song_limit - 1) ? ++current_song : 0; };
    const auto& prev = [&, this] { current_song = (current_song > 0) ? --current_song : current_song = song_limit - 1; };

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