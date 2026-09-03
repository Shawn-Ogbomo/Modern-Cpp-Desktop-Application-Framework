#include "../include/directory_manager.hpp"
#include "../include/music_player.hpp"
#include "../include/util.hpp"

using namespace std::chrono_literals;
namespace B_I = Button_Interface;
namespace fs = std::filesystem;
namespace rng = std::ranges;

Music_Player::Music_Player()
{
    Util::load_font(Directory_Manager::assets_dir()
        / "fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf", font);

    caption.setFillColor({ 236,203,180 });
    caption.setString("Song: ");
    caption.setCharacterSize(26);
    caption.setPosition({ 600, 842 });

    for (auto index = 0; const auto& song : fs::directory_iterator{ Directory_Manager::assets_dir()
        / "audio" })
    {
        songs.emplace_back(sf::Text{ font, song.path().filename().stem().string() }, song);

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

    for (auto internal_index = 0; const auto& texture : bm.textures)
    {
        buttons.push_back({ texture, internal_index, button_pos });
        ++internal_index;
        button_pos.x += 35;
    }
}

auto Music_Player::operator()(sf::RenderWindow& rw, sf::Vector2f cursor_pos)& -> void
{
    /// TODO: Template this to accommodate the pause, resume, and restart, yes and no.
    /// TODO: Make this a function; It will be used in Media_Button, General_Button, and Game_State_Button.
    const auto button = rng::find_if(buttons, [&](const auto& b) {
        return std::get<0>(b.forms).getGlobalBounds().contains(cursor_pos);
        });

    if (button != std::end(buttons))
    {
        rw.draw(std::get<1>(button->forms));
        rw.display();

        while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            rw.draw(std::get<2>(button->forms));
            rw.display();
        }

        if (const auto cursor_pos_released = static_cast<sf::Vector2f>(sf::Mouse::getPosition(rw));
            std::get<0>(button->forms).getGlobalBounds().contains(cursor_pos_released))
        {
            rw.draw(std::get<1>(button->forms));
            rw.display();

            rw.draw(std::get<0>(button->forms));
            rw.display();
            button->operator()(*this);
            return;
        }
    }

    idle(*this);
}

void Music_Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(caption);
    target.draw(songs[current_song].first);
    rng::for_each(buttons, [&target](const auto& b) {
        target.draw(b);
        });
}

auto Music_Player::idle(Music_Player& mp)& -> void
{
    if (!mp)
    {
        mode = B_I::ButtonMode::on;
        const auto& play = buttons[static_cast<int>((B_I::Button_Names::Media::play))];
        play.operator()(mp);
    }

    else if (const auto& done = songs[current_song].second; done.getPlayingOffset()
        >= done.getDuration() - 500000us)
    {
        const auto& next = buttons[static_cast<int>(B_I::Button_Names::Media::next)];
        next.operator()(mp);
    }
}