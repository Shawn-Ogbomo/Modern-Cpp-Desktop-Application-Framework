#include "../headers/music_player.hpp"
#include "../headers/util.hpp"

Music_Player::Music_Player()
{
	Util::load_font(std::filesystem::path{ "..\\" + std::string{"fonts/galafera-med-font/GalaferaMediumItalic-JpXJK.ttf"} }, font);

	auto index = 0;

	for (const auto& song : std::filesystem::directory_iterator{ "..\\music" })
	{
		songs.emplace_back(sf::Text{ font, song.path().filename().string() }, song);
		songs[index].first.setFillColor(font_color);
		songs[index].first.setPosition(sf::Vector2f{ 600,748 });
		songs[index].first.setCharacterSize(26);

		++index;
	}

	limit = songs.size();
}

void Music_Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(songs[current_song].first);
}