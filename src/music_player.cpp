#include "../include/music_player.hpp"
#include "../include/util.hpp"

using namespace std::chrono_literals;
namespace fs = std::filesystem;
namespace B_I = Button_Interface;

Music_Player::Music_Player()
{
	Util::load_font(std::string{ "fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf" }, font);
	caption.setFillColor(sf::Color{ 63, 59, 147 });
	caption.setString("Song: ");
	caption.setCharacterSize(26);
	caption.setPosition(sf::Vector2f{ 600,842 });

	for (auto index = 0; const auto& song : fs::directory_iterator{ "audio" })
	{
		songs.emplace_back(sf::Text{ font, song.path().filename().stem().string() }, song);

		auto& [name, file] = songs[index];

		name.setFillColor(sf::Color{ 63, 59, 147 });
		name.setPosition(sf::Vector2f{ 674,842 });
		name.setCharacterSize(26);

		++index;
	}

	limit = songs.size();

	bm.load_textures();

	buttons.reserve(bm.textures.size());

	auto button_pos = sf::Vector2f{ 452.0f - 35.0f,842.0f };

	for (auto internal_index = 0; const auto& texture :bm.textures)
	{
		buttons.push_back(Button{ texture,internal_index,button_pos });
		++internal_index;
		button_pos.x += 35;
	}
}

auto Music_Player::operator()(sf::RenderWindow& rw, sf::Vector2f cursor_pos) ->void
{
	const auto button = std::find_if(buttons.begin(), buttons.end(), [&](const auto& b) {
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
	std::for_each(buttons.begin(), buttons.end(), [&target](const auto& b) {target.draw(b); });
}

auto Music_Player::idle(Music_Player& mp) -> void
{
	if (!mp)
	{
		mode = B_I::ButtonMode::on;
		const auto& play = buttons[Util::to_int(B_I::ButtonName::play)];
		play.operator()(mp);
	}

	else if (const auto& done = songs[current_song].second; done.getPlayingOffset() >= done.getDuration() - 500000us)
	{
		const auto& next = buttons[Util::to_int(B_I::ButtonName::next)];
		next.operator()(mp);
	}
}

auto Button::operator()(Music_Player& mp)const ->void
{
	switch (name)
	{
	case B_I::ButtonName::prev:
		mp.stop();
		mp.prev();
		mp.play();
		break;
	case B_I::ButtonName::pause:
		mp.pause();
		break;
	case B_I::ButtonName::play:
		mp.play();
		break;
	case B_I::ButtonName::next:
		mp.stop();
		mp.next();
		mp.play();
		break;
	case B_I::ButtonName::stop:
		mp.stop();
		break;
	}
}