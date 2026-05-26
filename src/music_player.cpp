#include "../headers/music_player.hpp"

Music_Player::Music_Player()
{
	for (const auto& song : std::filesystem::directory_iterator{ "..\\music" })
	{
		songs.emplace_back(song.path().filename().string(), song);
	}

	limit = songs.size();
}

void Music_Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
}