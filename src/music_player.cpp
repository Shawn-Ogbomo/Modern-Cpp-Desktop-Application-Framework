#include "../include/directory_manager.hpp"
#include "../include/music_player.hpp"
#include "../include/util.hpp"

using namespace std::chrono_literals;
namespace D_M = Directory_Manager;
namespace fs = std::filesystem;
namespace B_N = Button_Names;
namespace rng = std::ranges;

Music_Player::Music_Player() : songs{ std::make_unique<sf::Music[]> (song_limit)}
{
    caption.setString("Song: ");
    caption.setCharacterSize(26);
    caption.setPosition({ 600, 842 });
    caption.setFillColor({ 236,203,180 });

    song_names.reserve(song_limit);

    for (auto index = 0; const auto& song : fs::directory_iterator{ D_M::assets_dir() / "audio" })
    {
        song_names.push_back({ Util::load_font()
            ,song.path().filename().stem().string() } );

        songs[index] = sf::Music{ song };

        song_names[index].setCharacterSize(26);
        song_names[index].setPosition({674, 842});
        song_names[index].setFillColor({236,203,180});

        ++index;
    }

    bm.load_textures();

    auto button_pos = sf::Vector2f{ 452.0f - 35.0f, 842.0f };

    for (auto internal_index = B_N::Media{}; const auto& texture : bm.textures)
    {
        buttons[static_cast<int>(internal_index)] 
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
    target.draw(song_names[current_song]);
    rng::for_each(buttons, [&target](const auto& button) { 
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