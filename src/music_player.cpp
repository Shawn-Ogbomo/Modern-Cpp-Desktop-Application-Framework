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

	const auto& textures = get_texture_manager().textures;
	const auto& size = textures.size();
	auto			   button_pos = sf::Vector2f{ 452.0f - 35.0f,842.0f };

	for (auto i = to_int(Texture_Manager_State::buttons); i < size;)
	{
		auto& button = buttons.emplace_back(Button{ textures[i++],textures[i++],textures[i++] });

		for (auto& internal_button : button.forms)
		{
			internal_button.setPosition(button_pos);
		}

		button_pos.x += 35;
	}
}

auto Music_Player::operator()(sf::RenderWindow& rw, sf::Vector2f cursor_pos) ->void
{
	const auto& [button_size_x, button_size_y] = buttons.front().forms.front().getLocalBounds().size;
	auto [button_pos_x, button_pos_y] = sf::Vector2f{};

	auto button = std::find_if(buttons.begin(), buttons.end(), [&](auto& b) {
		button_pos_x = b.forms.front().getPosition().x;
		button_pos_y = b.forms.front().getPosition().y;
		return (cursor_pos.x >= button_pos_x && cursor_pos.x <= button_pos_x + button_size_x
			&& cursor_pos.y >= button_pos_y && cursor_pos.y <= button_pos_y + button_size_y);
		});

	if (button != std::end(buttons))
	{
		rw.draw(button->forms[to_int(ButtonState::touched)]);
		rw.display();

		while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			rw.draw(button->forms[to_int(ButtonState::pushed)]);
			rw.display();
		}

		if (auto cursor_pos_released = static_cast<sf::Vector2f>(sf::Mouse::getPosition(rw));
			cursor_pos_released.x >= button_pos_x && cursor_pos_released.x <= button_pos_x + button_size_x
			&& cursor_pos_released.y >= button_pos_y && cursor_pos_released.y <= button_pos_y + button_size_y)
		{
			rw.draw(button->forms[to_int(ButtonState::touched)]);
			rw.display();

			rw.draw(button->forms[to_int(ButtonState::idle)]);
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

	for (auto& button : buttons)
	{
		target.draw(button);
	}
}

auto Music_Player::idle(Music_Player& mp) -> void
{
	if (auto song_finished = mp.songs[mp.current_song].second.getPlayingOffset() >= mp.songs[mp.current_song].second.getDuration() - std::chrono::microseconds{ 500000 })
	{
		auto& next = mp.buttons[to_int(ButtonName::next)];
		next.operator()(mp);
	}

	else if (static auto count = 0; !count)
	{
		auto& play = mp.buttons[to_int(ButtonName::play)];
		play.operator()(mp);

		++count;
	}
}

auto Button::operator()(Music_Player& mp) ->void
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