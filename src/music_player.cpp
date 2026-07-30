#include "../include/music_player.hpp"
#include "../include/util.hpp"

using namespace Button_Interface;

Music_Player::Music_Player()
{
	Util::load_font(std::filesystem::path{ "../" + std::string{"fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf"} }, font);
	caption.setFillColor(sf::Color{ 63, 59, 147 });
	caption.setString("Song: ");
	caption.setCharacterSize(26);
	caption.setPosition(sf::Vector2f{ 600,842 });

	for (auto index = 0; const auto& song : std::filesystem::directory_iterator{ "../audio" })
	{
		songs.emplace_back(sf::Text{ font, song.path().filename().stem().string() }, song);

		auto& [name, file] = songs[index];

		name.setFillColor(sf::Color{ 63, 59, 147 });
		name.setPosition(sf::Vector2f{ 674,842 });
		name.setCharacterSize(26);

		++index;
	}

	limit = songs.size();

	auto button_pos = sf::Vector2f{ 452.0f - 35.0f,842.0f };
	bm.load_textures();

	const auto sz = bm.textures.size();

	for(auto i = 0;  i < sz; ++i)
	{
		buttons.emplace_back(Button{bm.textures[i]});
		
		auto& [form_1, form_2,form_3] = buttons.back().forms;
		
		form_1.setPosition(button_pos);
		form_2.setPosition(button_pos);
		form_3.setPosition(button_pos);
		button_pos.x += 35;
	}
}

auto Music_Player::operator()(sf::RenderWindow& rw, sf::Vector2f cursor_pos) ->void
{
	const auto button = std::find_if(buttons.begin(), buttons.end(), [&](auto& b) {
		const auto [button_pos_x, button_pos_y] = std::get<0>(b.forms).getPosition();
		const auto& [button_size_x, button_size_y] = std::get<0>(b.forms).getLocalBounds().size;
		return (cursor_pos.x >= button_pos_x && cursor_pos.x <= button_pos_x + button_size_x
			&& cursor_pos.y >= button_pos_y && cursor_pos.y <= button_pos_y + button_size_y);
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
			cursor_pos_released.x >= std::get<0>(button->forms).getPosition().x
			&& cursor_pos_released.x <= std::get<0>(button->forms).getPosition().x + std::get<0>(button->forms).getLocalBounds().size.x
			&& cursor_pos_released.y >= std::get<0>(button->forms).getPosition().y
			&& cursor_pos_released.y <= std::get<0>(button->forms).getPosition().y + std::get<0>(button->forms).getLocalBounds().size.y)
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
	std::for_each(buttons.begin(), buttons.end(), [&target](const auto&b) {target.draw(b);});
}

auto Music_Player::idle(Music_Player& mp) -> void
{
	if (const auto song_finished = mp.songs[mp.current_song].second.getPlayingOffset() >= mp.songs[mp.current_song].second.getDuration() - std::chrono::microseconds{ 500000 })
	{
		const auto& next = mp.buttons[Util::to_int(ButtonName::next)];
		next.operator()(mp);
	}

	else if (static auto count = 0; !count)
	{
		const auto& play = mp.buttons[Util::to_int(ButtonName::play)];
		play.operator()(mp);

		++count;
	}
}

auto Button::operator()(Music_Player& mp)const ->void
{
	if (name == ButtonName::prev)
	{
		mp.stop();
		mp.prev();
		mp.play();
	}

	else if (name == ButtonName::pause)
	{
		mp.pause();
	}

	else if (name == ButtonName::play)
	{
		mp.play();
	}

	else if (name == ButtonName::next)
	{
		mp.stop();
		mp.next();
		mp.play();
	}

	else if (name == ButtonName::stop)
	{
		mp.stop();
	}
}