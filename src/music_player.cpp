#include <ranges>

#include "../include/music_player.hpp"
#include "../include/util.hpp"

Music_Player::Music_Player()
{
	Util::load_font(std::filesystem::path{ "..\\" + std::string{"fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf"} }, font);
	caption.setFillColor(sf::Color{ 63, 59, 147 });
	caption.setString("Song: ");
	caption.setCharacterSize(26);
	caption.setPosition(sf::Vector2f{ 600,842 });

	for (auto index =0; const auto& song : std::filesystem::directory_iterator{ "..\\audio" })
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
	const auto& size = static_cast<int>(textures.size());
	const auto button_pos_texture = 53;
	auto button_pos = sf::Vector2f{ 452.0f - 35.0f,842.0f };

	for (auto i = button_pos_texture; i< size;)
	{
		auto& button = buttons.emplace_back(Button{ textures[i++],textures[i++],textures[i++] });

		for (auto& button_state: button.forms)
		{
			button_state.setPosition(button_pos);
		}

		button_pos.x += 35;
	}
}

auto Music_Player::operator()(const sf::Clock& c, sf::RenderWindow &rw, sf::Vector2f cursor_pos) ->void
{
	const auto& [button_size_x, button_size_y] = buttons.front().forms.front().getLocalBounds().size;
	
	auto button = std::find_if(buttons.begin(), buttons.end(), [&](auto& b) {
		const auto& [button_pos_x, button_pos_y] = b.forms.front().getPosition();
		return (cursor_pos.x >= button_pos_x && cursor_pos.x <= button_pos_x + button_size_x
			&& cursor_pos.y >= button_pos_y && cursor_pos.y <= button_pos_y + button_size_y);
		});
	
	if (button != std::end(buttons))
	{
			rw.draw(button->forms[1]);
			rw.display();
			Util::delay_time(c, std::chrono::microseconds{ 20000 });
		
			while (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				rw.draw(button->forms.back());
				rw.display();
			}

			rw.draw(button->forms[1]);
			rw.display();
			Util::delay_time(c, std::chrono::microseconds{ 20000 });

			rw.draw(button->forms.front());
			rw.display();
			button->operator()(*this);
			return;
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

auto Music_Player::idle( Music_Player& mp) -> void
{
	if (auto song_finished = mp.songs[mp.current_song].second.getPlayingOffset() >= mp.songs[mp.current_song].second.getDuration() - std::chrono::microseconds{ 500000 })
	{
		auto& next = mp.buttons[3];
		next.operator()(mp);
	}

	else if  (static auto count = 0; !count)
	{
		auto& play = mp.buttons[2];
		play.operator()(mp);

		++count;
	}
}

auto Button::operator()(Music_Player& mp) ->void
{
	if (name == ButtonState::prev)
	{
		mp.stop();
		mp.prev();
		mp.play();
	}

	else if (name == ButtonState::pause)
	{
		mp.pause();
	}

	else if (name == ButtonState::play)
	{
		mp.play();
	}

	else if (name == ButtonState::next)
	{
		mp.stop();
		mp.next();
		mp.play();
	}

	else if (name == ButtonState::stop)
	{
		mp.stop();
	}
}