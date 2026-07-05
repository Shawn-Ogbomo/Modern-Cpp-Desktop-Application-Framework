#include "../include/music_player.hpp"
#include "../include/util.hpp"

Music_Player::Music_Player()
{
	Util::load_font(std::filesystem::path{ "..\\" + std::string{"fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf"} }, font);
	caption.setFillColor(sf::Color{ 63, 59, 147 });
	caption.setString("Song: ");
	caption.setCharacterSize(26);
	caption.setPosition(sf::Vector2f{ 600,842 });

	auto index = 0;

	for (const auto& song : std::filesystem::directory_iterator{ "..\\audio" })
	{
		songs.emplace_back(sf::Text{ font, song.path().filename().stem().string() }, song);
		songs[index].first.setFillColor(sf::Color{ 63, 59, 147 });
		songs[index].first.setPosition(sf::Vector2f{ 674,842 });
		songs[index].first.setCharacterSize(26);

		++index;
	}

	limit = songs.size();

	const auto& textures = get_texture_manager().textures;
	const auto& size = textures.size();

	auto pos_x = 452.0f - 35.0f;
	auto pos_y = 842.0f;
	auto internal_index = 0;
	auto button_pos_texture = 53;

	for (auto i = button_pos_texture, j = button_pos_texture + 1, k = button_pos_texture + 2; i < size; i = k + 1, j = i + 1, k = j + 1)
	{
		buttons.push_back(Button{ textures[i],textures[j],textures[k] });
		buttons[internal_index].forms[0].setPosition(sf::Vector2f{ pos_x,pos_y });
		buttons[internal_index].forms[1].setPosition(sf::Vector2f{ pos_x,pos_y });
		buttons[internal_index].forms[2].setPosition(sf::Vector2f{ pos_x,pos_y });

		++internal_index;
		pos_x += 35;
	}
}

auto Music_Player::operator()(Button& b) ->void
{
	if (b.name == ButtonState::prev)
	{
		stop();
		prev();
		play();
	}

	else if (b.name == ButtonState::pause)
	{
		pause();
	}

	else if( b.name == ButtonState::play)
	{
		play();
	}

	else if (b.name == ButtonState::next)
	{
		stop();
		next();
		play();
	}

	else if (b.name == ButtonState::stop)
	{
		stop();
	}

	b.clicked = false;
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

auto Music_Player::find_clicked_button(const sf::Vector2<float>& cursor_pos) ->std::vector<Button>::iterator
{
	return std::find_if(buttons.begin(), buttons.end(), [&cursor_pos](auto& b) {
		return (cursor_pos.x >= b.forms[0].getPosition().x && cursor_pos.x <= b.forms[0].getPosition().x + b.forms[0].getLocalBounds().size.x
			&& cursor_pos.y >= b.forms[0].getPosition().y && cursor_pos.y <= b.forms[0].getPosition().y + b.forms[0].getLocalBounds().size.y);
		});
}